/**
 * @file	Dx12CommandQueueManager.cpp
 * @brief	コマンドキュークラス実装.
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx12CommandQueueManager.h"


namespace Lib
{
	namespace Dx12
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		CommandQueueManager::CommandQueueManager()
		{
		}

		CommandQueueManager::~CommandQueueManager()
		{
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool CommandQueueManager::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			m_pGraphicsDevice = _pGraphicsDevice;
			return true;
		}

		void CommandQueueManager::Finalize()
		{
			for (auto itr = m_pCommandQueues.begin(); itr != m_pCommandQueues.end(); itr++)
			{
				SafeRelease(*itr);
			}

			m_pGraphicsDevice = nullptr;
		}

		bool CommandQueueManager::CreateCommandQueue(
			int* _pindex,
			CommandListManager::COMMAND_LIST_TYPE _type,
			int _priority)
		{
			return true;
		}
	}
}
