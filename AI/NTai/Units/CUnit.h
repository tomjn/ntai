/*
NTai
Tom J Nowell
tarendai@darkstars.co.uk
www.darkstars.co.uk
LGPL 2 licence 2004+
*/

namespace ntai {

	class CUnit : public IModule{
	public:
		CUnit();
		CUnit(Global* GL, int uid);
		virtual ~CUnit();
		
		bool operator==(int unit);

		bool Init();
		void RecieveMessage(CMessage &message);
		
		CUnitTypeData* GetUnitDataType();
		

		int GetID();
		int GetAge();

		void AddBehaviour(IBehaviour* b);

		void SetTaskManager(ITaskManager* taskManager);
		ITaskManager* GetTaskManager();

		void SetBehaviourManager(IBehaviourManager* behaviourManager);
		IBehaviourManager* GetBehaviourManager();
	protected:
		
		bool doingplan;
		uint curplan;
		ITaskManager* taskManager;
		IBehaviourManager* behaviourManager;
		bool under_construction;
		IModule* currentTask;
		std::list< IBehaviour* > behaviours;
		CUnitTypeData* utd;
		int uid;
		int birth;
	};
}
