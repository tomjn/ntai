#include "../Core/include.h"
#include "../Core/AIExport.h"

namespace ntai {
	CConfigData::CConfigData(Global* G){
		this->G = G;
		_abstract = true;
		gaia = false;
		spacemod = false;
		dynamic_selection = true;
		use_modabstracts = false;
		absent_abstract = false;
		fire_state_commanders = 0;
		move_state_commanders = 0;
		scout_speed = 60;
		rule_extreme_interpolate= true;
		mod_tdf = new TdfParser(G);
		
		//CLOG("Loading AI.tdf with TdfParser");
		/*TdfParser cs(G);
		cs.LoadFile("AI/AI.tdf");*/
		
		//CLOG("Retrieving datapath value");

		datapath = aiexport_getDataDir(true);//cs.SGetValueDef(std::string(, "AI/Skirmish/NTai/data");
		//datapath += "data\\";
		//datapath += slash;

		NLOG("Getting tdfpath value");
		
		NLOG("Loading modinfo.tdf");
		TdfParser sf(G);
		if(sf.LoadFile("modinfo.tdf")){
			G->L.print("modinfo.tdf loaded into parser");
		} else {
			G->L.eprint("error modinfo.tdf retrieval failed");
		}
		const char* modname = G->cb->GetModName();
		tdfpath =  sf.SGetValueDef(std::string(modname), "MOD\\ShortName");
	}

	CConfigData::~CConfigData(){
		//
		delete mod_tdf;
	}

	void CConfigData::Load(){
		//
		mod_tdf->GetDef(_abstract, "1", "AI\\abstract");
		mod_tdf->GetDef(gaia, "0", "AI\\GAIA");
		mod_tdf->GetDef(spacemod, "0", "AI\\spacemod");
		mod_tdf->GetDef(mexfirst, "0", "AI\\first_attack_mexraid");
		mod_tdf->GetDef(hardtarget, "0", "AI\\hard_target");
		mod_tdf->GetDef(mexscouting, "1", "AI\\mexscouting");
		mod_tdf->GetDef(dynamic_selection, "1", "AI\\dynamic_selection");
		mod_tdf->GetDef(use_modabstracts, "0", "AI\\use_mod_default");
		mod_tdf->GetDef(absent_abstract, "1", "AI\\use_mod_default_if_absent");
		mod_tdf->GetDef(rule_extreme_interpolate, "1", "AI\\rule_extreme_interpolate");
		antistall = atoi(mod_tdf->SGetValueDef("4", "AI\\antistall").c_str());
		Max_Stall_TimeMobile = (float)atof(mod_tdf->SGetValueDef("0", "AI\\MaxStallTime").c_str());
		Max_Stall_TimeIMMobile = (float)atof(mod_tdf->SGetValueDef(mod_tdf->SGetValueDef("0", "AI\\MaxStallTime"), "AI\\MaxStallTimeimmobile").c_str());

		fire_state_commanders = atoi(mod_tdf->SGetValueDef("0", "AI\\fire_state_commanders").c_str());
		move_state_commanders = atoi(mod_tdf->SGetValueDef("0", "AI\\move_state_commanders").c_str());
		scout_speed = (float)atof(mod_tdf->SGetValueDef("50", "AI\\scout_speed").c_str());

		if(_abstract == true){
			G->L.print("abstract is true, turning on dynamic selection");
			dynamic_selection = true;
		}

		if(use_modabstracts == true){
			_abstract = false;
		}

		if(dynamic_selection){
			G->L.print("dynamic selection is on");
		}else{
			G->L.print("dynamic selection is off");
		}
	}
}
