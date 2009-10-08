namespace ntai {
	class CConfigBehaviourManager : public IBehaviourManager {
	public:
		CConfigBehaviourManager(Global* G, CUnit* u);

		virtual bool Init(){ return true;}
		virtual void RecieveMessage(CMessage &message){}

		virtual void AddBehaviour(IBehaviour* b);
		virtual void DeleteBehaviour(IBehaviour* b);

		virtual void LoadBehaviours();

	protected:
		CUnit* u;
	};
}
