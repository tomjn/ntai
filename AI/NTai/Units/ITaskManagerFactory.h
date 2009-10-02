/*
AF 2004+
LGPL 2
*/

namespace ntai {
	class ITaskManagerFactory : public IModule {
	public:
		virtual ITaskManager* GetTaskManager(CUnit* unit) = 0;
	};
}
