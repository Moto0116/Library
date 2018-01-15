/**
 * @file	Dx12CommandQueue.h
 * @brief	コマンドキュークラス定義
 * @author	morimoto
 */
#ifndef LIB_DX12_COMMANDQUEUE_H
#define LIB_DX12_COMMANDQUEUE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3D12.h>
#include <DXGI1_4.h>

#include "..\..\GraphicsDevice\Dx12GraphicsDevice.h"
#include "..\Dx12CommandQueueManager.h"


namespace Lib
{
	namespace Dx12
	{
		/*** コマンドキュークラス */
		class CommandQueue
		{
		public:
			/**
			 * コンストラクタ
			 * @param[in] _type 作成するコマンドキューの種類
			 * @param[in] _priority コマンドキューの優先度
			 */
			CommandQueue(
				GraphicsDevice*	_pDevice,
				D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT,
				int _priority = 0);

			/*** デストラクタ */
			~CommandQueue();

			/**
			 * コマンドキューの取得
			 * @return コマンドキュー
			 */
			ID3D12CommandQueue* Get() const { return m_pCommandQueue; }

		private:
			/*** 初期化処理 */
			void Initialize();

			/*** 終了処理 */
			void Finalize();

			GraphicsDevice*					m_pGraphicsDevice;	//!< グラフィックスデバイス.
			ID3D12CommandQueue*				m_pCommandQueue;	//!< コマンドキュー.
			ID3D12Fence*					m_pFence;			//!< フェンス.
			int								m_FenceValue;		//!< フェンス値.
			HANDLE							m_FenceEventHandle;	//!< フェンスのイベントハンドル.
			D3D12_COMMAND_LIST_TYPE			m_Type;				//!< コマンドキューの種類.
			int								m_Priority;			//!< コマンドキューの優先度.

		};
	}
}


#endif // !LIB_DX12_COMMANDQUEUE_H
