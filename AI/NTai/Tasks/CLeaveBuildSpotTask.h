
namespace ntai {
	class CLeaveBuildSpotTask : public IModule {
	public:
		CLeaveBuildSpotTask(Global* GL, int unit, CUnitTypeData* ud);
		void RecieveMessage(CMessage &message);
		bool Init();
		void End();
	protected:
		std::string mymessage;
		int unit;
		CUnitTypeData* utd;
	};
}
