
namespace ntai {
	//
	class CConstructionPlacerFactory {
	public:
		
		CConstructionPlacerFactory();
		~CConstructionPlacerFactory();
		
		
		IConstructionPlacer* GetPlacerFor(CUnitTypeData* unitType);

		void AddPlacer(IConstructionPlacer* p);
		void RemovePlacer(IConstructionPlacer* p);
	};
}
