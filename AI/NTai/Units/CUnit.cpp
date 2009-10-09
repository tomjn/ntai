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

		taskManager->Init();
		behaviourManager->Init();
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
						currentTask = 0;
						/*taskManager->GetNextTask();
						if(currentTask != 0){
							currentTask->Init();
							G->RegisterMessageHandler(currentTask);
						}else{
							currentTask = 0;
						}*/
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
				behaviourManager->LoadBehaviours();
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
