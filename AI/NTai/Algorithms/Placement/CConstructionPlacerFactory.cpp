#include "../../Core/include.h"

namespace ntai {

	CConstructionPlacerFactory::CConstructionPlacerFactory(){
		//
	}
	
	CConstructionPlacerFactory::~CConstructionPlacerFactory(){
		//
	}

	IConstructionPlacer* CConstructionPlacerFactory::GetPlacerFor(CUnitTypeData* unitType){
		//
		return 0;
	}

	void CConstructionPlacerFactory::AddPlacer(IConstructionPlacer* p){
		//
	}

	void CConstructionPlacerFactory::RemovePlacer(IConstructionPlacer* p){
		//
	}
}
