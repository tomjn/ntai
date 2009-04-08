/*
AF 2004+
LGPL 2
*/

namespace ntai {
	class ITaskManager : public IModule {
	public:
		virtual void TaskFinished()=0;
		virtual IModule* GetNextTask() = 0;
		virtual bool HasTasks()=0;

		virtual void RemoveAllTasks()=0;
	};
}
