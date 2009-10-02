// 

namespace ntai {

	class CUnitDefLoader{
	public:
		CUnitDefLoader(Global* GL);
		~CUnitDefLoader();
		void Init();
		
		const UnitDef* GetUnitDef(std::string name) const;
		const UnitDef* GetUnitDefByIndex(int i) const;
		
		CUnitTypeData* GetUnitTypeDataByUnitId(int uid) const;
		CUnitTypeData* GetUnitTypeDataById(int id) const;
		CUnitTypeData* GetUnitTypeDataByName(std::string name) const;
		
		bool HasUnit(std::string name) const;
	private:
		int GetIdByName(std::string name) const;

		Global* G;

		std::map<std::string,int> defs;
		std::map<int,CUnitTypeData* > type_data;

		const UnitDef** UnitDefList;
		int unum;
	};
}
