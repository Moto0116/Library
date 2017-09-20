/**
 * @file	TaskManager_private.inl
 * @brief	タスク管理の基底クラステンプレート実装
 * @author	morimoto
 */
#ifndef LIB_TASKMANAGER_PRIVATE_H
#define LIB_TASKMANAGER_PRIVATE_H


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	template <typename Type, typename StartUpTask>
	inline TaskManager<Type, StartUpTask>::TaskManager()
	{
	}

	template <typename Type, typename StartUpTask>
	inline TaskManager<Type, StartUpTask>::~TaskManager()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::Run()
	{
		m_pStartUpTaskList.sort(StartUpTask::TaskCmp());
		for (auto itr = m_pStartUpTaskList.begin(); itr != m_pStartUpTaskList.end(); itr++)
		{
			(*itr)->Run();
		}

		m_pTaskList.sort(Type::TaskCmp());
		for (auto itr = m_pTaskList.begin(); itr != m_pTaskList.end(); itr++)
		{
			(*itr)->Run();
		}
	}

	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::AddTask(Type* _pTask)
	{
		m_pTaskList.push_back(_pTask);
	}

	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::RemoveTask(Type* _pTask)
	{
		for (auto itr = m_pTaskList.begin(); itr != m_pTaskList.end(); itr++)
		{
			if (_pTask->GetID() == (*itr)->GetID())
			{
				m_pTaskList.erase(itr);
				break;
			}
		}
	}

	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::AddStartUpTask(StartUpTask* _pStartUpTask)
	{
		m_pStartUpTaskList.push_back(_pStartUpTask);
	}

	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::RemoveStartUpTask(StartUpTask* _pStartUpTask)
	{
		for (auto itr = m_pStartUpTaskList.begin(); itr != m_pStartUpTaskList.end(); itr++)
		{
			if (_pStartUpTask->GetID() == (*itr)->GetID())
			{
				m_pStartUpTaskList.erase(itr);
				break;
			}
		}
	}
}


#endif // !LIB_TASKMANAGER_PRIVATE_H
