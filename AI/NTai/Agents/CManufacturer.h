//New construction system

namespace ntai {

	class CBPlan {//: public boost::noncopyable{ // This is not used for factories building units.
	public:
		CBPlan();
	//	CBPlan();
		~CBPlan();

		bool IsValid(){
			return valid;
		}
		//bool HasBuilder(int i);
		void AddBuilder(int i);
		bool HasBuilders();
		void RemoveBuilder(int i);
		void RemoveAllBuilders();
		int GetBuilderCount();

		uint id;


		int subject;					// the thing being built
		bool started;					// has construction started?
		float3 pos;						// where is the unit being built? Used to tie the new unit to the plan
		CUnitTypeData* utd;
		float radius;
		bool inFactory;
	private:
		bool valid;
		int bcount;
		//boost::mutex plan_mutex;
		//std::set<int> builders;				// the builder

	};

	class SkyWrite{
	public:
		SkyWrite(IAICallback* cb);
		virtual ~SkyWrite();
		void Write(std::string Text, float3 loc, float Height=25, float Width=20, int Duration= 500, float Red=1.0f, float Green=1.0f, float Blue=1.0f, float Alpha=1.0f);
		IAICallback *GS;
	};

	class CManufacturer : public IModule {
	public:
		CManufacturer(Global* GL);
		virtual ~CManufacturer();
		bool Init();
		void RecieveMessage(CMessage &message);
		void UnitCreated(int uid);
		void UnitFinished(int uid);
		void UnitIdle(int uid);
		void UnitMoveFailed(int uid);
		void UnitDestroyed(int uid);
		void Update();
		float3 GetBuildPos(int builder, const UnitDef* target, const UnitDef* builderdef, float3 unitpos);

		std::map<std::string,btype> types;
		std::map<btype,std::string> typenames;

		btype GetTaskType(std::string s);						// retrieves the associated tasktype
		std::string GetTaskName(btype type);						// retrieves the associated taskname

		void RegisterTaskPair(std::string name, btype type);		// registers this pair so it can be logged and used in the tasklists
		void RegisterTaskTypes();

		bool CanBuild(int uid,const UnitDef* ud, std::string name);

		std::deque<CBPlan* >* BPlans;

		//bool WipePlansForBuilder(int unit);

		//int WhatIsUnitBuilding(int builder);

		//bool UnitTargetStartedBuilding(int builder);

		std::deque<CBPlan* >::iterator OverlappingPlans(float3 pos,const UnitDef* ud);

		uint getplans();
		void AddPlan();
		void RemovePlan();

	private:
		std::map<int,bool> factorytechlevels;
		std::map<int,std::vector<float3> > techfactorypositions;

		Global* G;
		bool initialized;
	};
}
