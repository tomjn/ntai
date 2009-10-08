
namespace ntai {

	class IBehaviourManager  : public IModule {
	public:
		IBehaviourManager(){}
		IBehaviourManager(Global* G, CUnit* u){}

		virtual void AddBehaviour(IBehaviour* b)=0;
		virtual void DeleteBehaviour(IBehaviour* b)=0;

		virtual void LoadBehaviours()=0;
	};

}
