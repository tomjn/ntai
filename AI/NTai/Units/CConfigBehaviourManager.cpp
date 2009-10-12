#include "../Core/include.h"

namespace ntai {
	CConfigBehaviourManager::CConfigBehaviourManager(Global* G, CUnit* u){
		this->G = G;
		this->u = u;
	}

	void CConfigBehaviourManager::AddBehaviour(IBehaviour* b){
		//
	}

	void CConfigBehaviourManager::DeleteBehaviour(IBehaviour* b){
		//
	}

	void CConfigBehaviourManager::LoadBehaviours(){
		std::string d = G->Get_mod_tdf()->SGetValueDef("auto","AI\\behaviours\\"+u->GetUnitDataType()->GetName());

		std::vector<std::string> v;
		CTokenizer<CIsComma>::Tokenize(v, d, CIsComma());

		if(!v.empty()){
			for(std::vector<std::string>::iterator vi = v.begin(); vi != v.end(); ++vi){

				std::string s = *vi;

				trim(s);
				tolowercase(s);

				if(s == "none"){
					break;
				} else if(s == "metalmaker"){
					CMetalMakerBehaviour* m = new CMetalMakerBehaviour(G, u->GetID());
					u->AddBehaviour(m);
				} else if(s == "attacker"){
					CAttackBehaviour* a = new CAttackBehaviour(G, u->GetID());
					u->AddBehaviour(a);
				} else if(s == "dgun"){
					CDGunBehaviour* a = new CDGunBehaviour(G, u->GetID());
					u->AddBehaviour(a);
				} else if(s == "retreat"){
					CRetreatBehaviour* a = new CRetreatBehaviour(G, u->GetID());
					u->AddBehaviour(a);
				} else if(s == "kamikaze"){
					CKamikazeBehaviour* a = new CKamikazeBehaviour(G, u->GetID());
					u->AddBehaviour(a);
				} else if(s == "staticdefence"){
					CStaticDefenceBehaviour* a = new CStaticDefenceBehaviour(G, u->GetID());
					u->AddBehaviour(a);
				} else if(s == "movefailreclaim"){
					CMoveFailReclaimBehaviour* a = new CMoveFailReclaimBehaviour(G, u->GetID());
					u->AddBehaviour(a);
				} else if(s == "auto"){
					// we have to decide what this units behaviours should be automatically
					// check each type of unit for pre-requisites and then assign the behaviour
					// accordingly.

					if(u->GetUnitDataType()->IsAttacker()){
						CAttackBehaviour* a = new CAttackBehaviour(G, u->GetID());
						u->AddBehaviour(a);
					}

					if(u->GetUnitDataType()->IsMetalMaker()){/*||(u->GetUnitDataType()->IsMex() && u->GetUnitDataType()->GetUnitDef()->onoffable )){*/ 
						CMetalMakerBehaviour* m = new CMetalMakerBehaviour(G, u->GetID());
						u->AddBehaviour(m);
						
					}
					
					if(u->GetUnitDataType()->CanDGun()){
						CDGunBehaviour* a = new CDGunBehaviour(G, u->GetID());
						u->AddBehaviour(a);
					}

					if(u->GetUnitDataType()->IsMobile()){
						CRetreatBehaviour* a = new CRetreatBehaviour(G, u->GetID());
						u->AddBehaviour(a);

						if(u->GetUnitDataType()->GetUnitDef()->canReclaim){
							CMoveFailReclaimBehaviour* mb = new CMoveFailReclaimBehaviour(G, u->GetID());
							u->AddBehaviour(mb);
						}

					}else{
						/* this unit can't move, if it can fire a weapon though give it
						   the static defence behaviour*/

						if(u->GetUnitDataType()->GetUnitDef()->weapons.empty()==false){
							CStaticDefenceBehaviour* a = new CStaticDefenceBehaviour(G, u->GetID());
							u->AddBehaviour(a);
						}
					}

					/*At the moment I can't think of a viable way of testing for the kamakaze
					  behaviour. It's usually a specialized behaviour though so a modder is
					  likely to mark it out in toolkit as a kamikaze unit
					*/

				}
			}
		}
	}
}
