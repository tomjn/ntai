/*
NTai
Tom J Nowell
tarendai@darkstars.co.uk
www.darkstars.co.uk
LGPL 2 licence 2004+
*/

#include "../Core/include.h"

namespace ntai {

	CUnit::CUnit(){
		G = 0;
		valid=false;
	}

	CUnit::CUnit(Global* GL, int uid){
		G = GL;
		
		NLOG("CUnit::CUnit");
		
		valid = true;
		
		if(!ValidUnitID(uid)){
			valid = false;
		}
		
		this->uid = uid;
		
		utd = G->UnitDefLoader->GetUnitTypeDataByUnitId(uid);

		if(utd==0){
			//
			G->L.eprint("ERROR IN CUNIT :: UTD == 0, ntai failed to retrieve the units unitdef object, something has gone wrong somewhere.");
			valid = false;
		}
		
		if(!valid){
			return;
		}

		if(!utd->IsMobile()){
			G->BuildingPlacer->Block(G->GetUnitPos(uid),utd);
		}
		currentTask = 0;
		doingplan=false;
		curplan=0;
		birth = G->GetCurrentFrame();
		//nolist=false;
		under_construction = true;
	}

	CUnit::~CUnit(){
		delete taskManager;
		if(behaviours.empty() == false){
			std::list<IBehaviour* >::iterator i = behaviours.begin();
			for(; i != behaviours.end(); ++i){
				IBehaviour* b = (*i);
				G->RemoveHandler(b);
				delete b;
			}
			behaviours.erase(behaviours.begin(),behaviours.end());
			behaviours.clear();
		}
	}

	bool CUnit::Init(){

		NLOG("CUnit::Init");
		if((G->GetCurrentFrame() > 32) && utd->IsMobile()){
			currentTask = new CLeaveBuildSpotTask(G,uid,utd);
			currentTask->Init();
			G->RegisterMessageHandler(currentTask);
		}
		return true;
	}

	void CUnit::RecieveMessage(CMessage &message){
		NLOG("CUnit::RecieveMessage");
		if(!IsValid()){
			return;
		}
		if(message.GetType() == std::string("update")){
			if(under_construction){
				return;
			}

			if(EVERY_((GetAge()%32+20))){
				if(currentTask != 0){
					if(!currentTask->IsValid()){
						//
						taskManager->TaskFinished();
						currentTask = taskManager->GetNextTask();
						if(currentTask != 0){
							currentTask->Init();
							G->RegisterMessageHandler(currentTask);
						}else{
							currentTask = 0;
						}
					}
				}else{
					//
					currentTask = taskManager->GetNextTask();
					if(currentTask != 0){
						currentTask->Init();
						G->RegisterMessageHandler(currentTask);
					}
				}

			}

		}else if(message.GetType() == std::string("unitfinished")){
			if(message.GetParameter(0) == this->uid){
				under_construction = false;
				LoadBehaviours();
			}
		}else if(message.GetType() == std::string("unitdestroyed")){
			if(message.GetParameter(0) == uid){

				if(!utd->IsMobile()){
					G->BuildingPlacer->UnBlock(G->GetUnitPos(uid),utd);
				}

				G->RemoveHandler(currentTask);
				taskManager->RemoveAllTasks();
				//G->RemoveHandler(taskManager);

				this->End();
				return;
			}
		}
		if(under_construction){
			return;
		}

	}

	int CUnit::GetAge(){
		NLOG("CUnit::GetAge");
		return G->GetCurrentFrame()-birth;
	}

	CUnitTypeData* CUnit::GetUnitDataType(){
		NLOG("CBuilder::GetUnitDataType");
		return utd;
	}

	bool CUnit::operator==(int unit){
		NLOG("CUnit::operator==");
		if(valid == false){
			return false;
		}
		if(unit == uid){
			return true;
		}else{
			return false;
		}
	}

	int CUnit::GetID(){
		NLOG("CUnit::GetID");
		return uid;
	}

	bool CUnit::LoadBehaviours(){
		std::string d = G->Get_mod_tdf()->SGetValueDef("auto","AI\\behaviours\\"+utd->GetName());

		std::vector<std::string> v;
		CTokenizer<CIsComma>::Tokenize(v, d, CIsComma());

		if(!v.empty()){
			for(std::vector<std::string>::iterator vi = v.begin(); vi != v.end(); ++vi){

				std::string s = *vi;

				trim(s);
				tolowercase(s);

				if(s == "none"){
					return true;
				} else if(s == "metalmaker"){
					CMetalMakerBehaviour* m = new CMetalMakerBehaviour(G, GetID());
					AddBehaviour(m);
				} else if(s == "attacker"){
					CAttackBehaviour* a = new CAttackBehaviour(G, GetID());
					AddBehaviour(a);
				} else if(s == "dgun"){
					CDGunBehaviour* a = new CDGunBehaviour(G, GetID());
					AddBehaviour(a);
				} else if(s == "retreat"){
					CRetreatBehaviour* a = new CRetreatBehaviour(G, GetID());
					AddBehaviour(a);
				} else if(s == "kamikaze"){
					CKamikazeBehaviour* a = new CKamikazeBehaviour(G, GetID());
					AddBehaviour(a);
				} else if(s == "staticdefence"){
					CStaticDefenceBehaviour* a = new CStaticDefenceBehaviour(G, GetID());
					AddBehaviour(a);
				} else if(s == "movefailreclaim"){
					CMoveFailReclaimBehaviour* a = new CMoveFailReclaimBehaviour(G, GetID());
					AddBehaviour(a);
				} else if(s == "auto"){
					// we have to decide what this units behaviours should be automatically
					// check each type of unit for pre-requisites and then assign the behaviour
					// accordingly.

					if(utd->IsAttacker()){
						CAttackBehaviour* a = new CAttackBehaviour(G, GetID());
						AddBehaviour(a);
					}

					if(utd->IsMetalMaker()||(utd->IsMex() && utd->GetUnitDef()->onoffable ) ){
						CMetalMakerBehaviour* m = new CMetalMakerBehaviour(G, GetID());
						AddBehaviour(m);
						
					}
					
					if(utd->CanDGun()){
						CDGunBehaviour* a = new CDGunBehaviour(G, GetID());
						AddBehaviour(a);
					}

					

					if(utd->GetUnitDef()->canmove || utd->GetUnitDef()->canfly){
						CRetreatBehaviour* a = new CRetreatBehaviour(G, GetID());
						AddBehaviour(a);

						if(utd->GetUnitDef()->canReclaim){
							CMoveFailReclaimBehaviour* mb = new CMoveFailReclaimBehaviour(G, GetID());
							AddBehaviour(mb);
						}

					}else{
						/* this unit can't move, if it can fire a weapon though give it
						   the static defence behaviour*/

						if(utd->GetUnitDef()->weapons.empty()==false){
							CStaticDefenceBehaviour* a = new CStaticDefenceBehaviour(G, GetID());
							AddBehaviour(a);
						}
					}

					/*At the moment I can't think of a viable way of testing for the kamakaze
					  behaviour. It's usually a specialized behaviour though so a modder is
					  likely to mark it out in toolkit as a kamikaze unit
					*/

				}
			}
		} else {
			//
			int a = 5;
		}
		return true;
	}
	
	void CUnit::AddBehaviour(IBehaviour* b){
		behaviours.push_back(b);
		b->Init();
		G->RegisterMessageHandler(b);
	}

	void CUnit::SetTaskManager(ITaskManager* taskManager){
		//
		this->taskManager = taskManager;
	}

	ITaskManager* CUnit::GetTaskManager(){
		//
		return taskManager;
	}
	
	void CUnit::SetBehaviourManager(IBehaviourManager* behaviourManager){
		//
		this->behaviourManager = behaviourManager;
	}

	IBehaviourManager* CUnit::GetBehaviourManager(){
		//
		return behaviourManager;
	}
}
