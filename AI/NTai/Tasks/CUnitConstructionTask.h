namespace ntai {
	class CUnitConstructionTask : public ITask {
	public:
		CUnitConstructionTask(Global* GL, int unit, CUnitTypeData* builder, CUnitTypeData* building);
		virtual ~CUnitConstructionTask();
		void RecieveMessage(CMessage &message);
		bool Init();
		void End();
	protected:
		std::string mymessage;
		int unit;
		CUnitTypeData* builder;
		CUnitTypeData* building;
	};
}
