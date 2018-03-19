/**
 * @file	Dx12CommandList.h
 * @brief	コマンドリストクラス定義
 * @author	morimoto
 */
#ifndef LIB_DX12_COMMANDLIST_H
#define LIB_DX12_COMMANDLIST_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\GraphicsDevice\Dx12GraphicsDevice.h"
#include "..\Dx12CommandListManager.h"


namespace Lib
{
	namespace Dx12
	{
		/*** コマンドリストクラス */
		class CommandList
		{
		public:
			/**
			 * コンストラクタ
			 * @param[in] _pDevice グラフィックデバイス
			 * @param[in] _type コマンドの種類
			 * @return 成功したらtrue 失敗したらfalse
			 */
			CommandList(
				GraphicsDevice* _pDevice,
				D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT);

			/*** デストラクタ */
			~CommandList();

			/**
			 * コマンドリストの取得
			 * @return コマンドリスト
			 */
			ID3D12GraphicsCommandList* GetCommandList() { return m_pCommandList; }

			/**
			 * コマンドアロケータの取得
			 * @return コマンドアロケータ
			 */
			ID3D12CommandAllocator* GetCommandAllocator() { return m_pCommandAllocator; }

		private:
			/*** 初期化処理 */
			void Initialize();

			/*** 終了処理 */
			void Finalize();

			GraphicsDevice*				m_pGraphicsDevice;		//!< グラフィックスデバイス.
			ID3D12CommandAllocator*		m_pCommandAllocator;	//!< コマンドアロケータ.
			ID3D12GraphicsCommandList*	m_pCommandList;			//!< コマンドリスト.
			D3D12_COMMAND_LIST_TYPE		m_CommandType;			//!< コマンドの種類.

		};
	}
}


#endif // !LIB_DX12_COMMANDLIST_H
