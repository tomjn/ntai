
namespace ntai {

	class CConsoleTask : public IModule {
	public:
		CConsoleTask(Global* GL);
		CConsoleTask(Global* GL, std::string message);
		void RecieveMessage(CMessage &message);
		bool Init();
	protected:
		std::string mymessage;
	};
}
