/**
 * @file	Dx12CommandListManager.h
 * @brief	コマンドリスト管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_DX12_COMMANDLISTMANAGER_H
#define LIB_DX12_COMMANDLISTMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\SingletonBase\SingletonBase.h"

#include <D3D12.h>
#include <vector>
#include "..\GraphicsDevice\Dx12GraphicsDevice.h"


namespace Lib
{
	namespace Dx12
	{
		/**
		 * コマンドリスト管理クラス
		 */
		class CommandListManager : public SingletonBase<CommandListManager>
		{
		public:
			/**
			 * コマンドリストの種類
			 */
			enum COMMAND_LIST_TYPE
			{
				COMMAND_LIST_TYPE_DIRECT = 0,	//!< 描画関係のコマンド.
				COMMAND_LIST_TYPE_BUNDLE = 1,	//!< バンドル用コマンド.
				COMMAND_LIST_TYPE_COMPUTE = 2,	//!< コンピュートシェーダー用コマンド.
				COMMAND_LIST_TYPE_COPY = 3,		//!< リソースコピー用コマンド.
				COMMAND_LIST_TYPE_MAX			//!< コマンド種類数.
			};

			friend SingletonBase<CommandListManager>;

			/**
			 * 初期化処理
			 * @param[in] _pGraphicsDevice コマンドキュー作成用グラフィックデバイス
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool Initialize(GraphicsDevice* _pGraphicsDevice);

			/**
			 * 終了処理
			 */
			void Finalize();

		private:
			/**
			 * コンストラクタ
			 */
			CommandListManager();

			/**
			 * デストラクタ
			 */
			virtual ~CommandListManager();


			GraphicsDevice*					m_pGraphicsDevice;	//!< グラフィックデバイス.
			std::vector<ID3D12CommandList*> m_pCommandLists;	//!< コマンドリスト.

		};
	}
}


#endif // !LIB_DX12_COMMANDLISTMANAGER_H
