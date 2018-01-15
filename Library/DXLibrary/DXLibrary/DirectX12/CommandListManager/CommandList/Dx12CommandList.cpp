/**
 * @file	Dx12CommandList.cpp
 * @brief	コマンドリストクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx12CommandList.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	namespace Dx12
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		CommandList::CommandList(GraphicsDevice* _pDevice, D3D12_COMMAND_LIST_TYPE _type) :
			m_pGraphicsDevice(_pDevice),
			m_pCommandAllocator(nullptr),
			m_pCommandList(nullptr),
			m_CommandType(_type)
		{
			Initialize();
		}

		CommandList::~CommandList()
		{
			Finalize();
		}


		//----------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------
		void CommandList::Initialize()
		{
			// コマンドアロケータの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateCommandAllocator(
				m_CommandType,
				__uuidof(*(m_pCommandAllocator)),
				reinterpret_cast<void**>(&m_pCommandAllocator))))
			{
				OutputErrorLog("コマンドアロケータの生成に失敗しました");
				return;
			}

			// コマンドリストの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateCommandList(
				0,
				m_CommandType,
				m_pCommandAllocator,
				nullptr,
				__uuidof(*(m_pCommandList)),
				reinterpret_cast<void**>(&m_pCommandList))))
			{
				OutputErrorLog("コマンドリストの生成に失敗しました");
				return;
			}
		}

		void CommandList::Finalize()
		{
			SafeRelease(m_pCommandList);
			SafeRelease(m_pCommandAllocator);
		}
	}
}

