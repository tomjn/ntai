namespace ntai {
	class CKeywordConstructionTask : public ITask {
	public:
		CKeywordConstructionTask(Global* GL, int unit, btype type);
		void RecieveMessage(CMessage &message);
		bool Init();
		void Build();
		void End();
	protected:
		int unit;
		btype type;
		CUnitTypeData* building;
		CUnitTypeData* utd;
	};
}
