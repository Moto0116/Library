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
#ifdef _DEBUG
		m_pConsoleWindow = new Debugger::ConsoleWindow();
		m_pConsoleWindow->Initialize("TaskManager-Debug");

		m_pDebugTimer = new Debugger::DebugTimer();
		m_pDebugTimer2 = new Debugger::DebugTimer();
#endif // _DEBUG
	}

	template <typename Type, typename StartUpTask>
	inline TaskManager<Type, StartUpTask>::~TaskManager()
	{
#ifdef _DEBUG
		SafeDelete(m_pDebugTimer2);
		SafeDelete(m_pDebugTimer);

		m_pConsoleWindow->Finalize();
		SafeDelete(m_pConsoleWindow);
#endif // _DEBUG
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::Run()
	{
#ifdef _DEBUG

		m_pDebugTimer2->StartTimer();	// タスク全体の作業時間計測開始.

		m_pConsoleWindow->Print("\n--------------------%s--------------------\n",
			Debugger::TypeToString<StartUpTask>());

		// 起動時実行タスクの処理.
		m_pStartUpTaskList.sort(StartUpTask::TaskCmp());
		for (auto itr = m_pStartUpTaskList.begin(); itr != m_pStartUpTaskList.end(); itr++)
		{
			// タスクの作業時間計測.
			m_pDebugTimer->StartTimer();
			(*itr)->Run();
			m_pDebugTimer->EndTimer();

			m_pConsoleWindow->Print(
				"Name : %s - Time : %d ms\n",
				(*itr)->GetName(),
				m_pDebugTimer->GetMilliSecond());
		}


		m_pConsoleWindow->Print("\n--------------------%s--------------------\n",
			Debugger::TypeToString<Type>());

		// 実行タスクの処理.
		m_pTaskList.sort(Type::TaskCmp());
		for (auto itr = m_pTaskList.begin(); itr != m_pTaskList.end(); itr++)
		{
			// タスクの作業時間計測.
			m_pDebugTimer->StartTimer();
			(*itr)->Run();
			m_pDebugTimer->EndTimer();

			m_pConsoleWindow->Print(
				"Name : %s - Time : %d ms\n",
				(*itr)->GetName(),
				m_pDebugTimer->GetMilliSecond());
		}

		m_pDebugTimer2->EndTimer();	// タスク全体の作業時間計測終了.
		m_pConsoleWindow->Print(
			"\nResult : %d ms\n",
			m_pDebugTimer2->GetMilliSecond());

#else // _DEBUG

		// 起動時実行タスクの処理.
		m_pStartUpTaskList.sort(StartUpTask::TaskCmp());
		for (auto itr = m_pStartUpTaskList.begin(); itr != m_pStartUpTaskList.end(); itr++)
		{
			// タスクの作業時間計測.
			(*itr)->Run();
		}

		// 実行タスクの処理.
		m_pTaskList.sort(Type::TaskCmp());
		for (auto itr = m_pTaskList.begin(); itr != m_pTaskList.end(); itr++)
		{
			// タスクの作業時間計測.
			(*itr)->Run();
		}

#endif // !_DEBUG
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
