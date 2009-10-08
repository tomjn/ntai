namespace ntai {
	class CConfigBehaviourManager : public IBehaviourManager {
	public:
		CConfigBehaviourManager(Global* G, CUnit* u);

		virtual void AddBehaviour(IBehaviour* b);
		virtual void DeleteBehaviour(IBehaviour* b);

		virtual void LoadBehaviours();
	};
}
