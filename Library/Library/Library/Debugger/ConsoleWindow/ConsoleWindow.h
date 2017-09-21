/**
 * @file	ConsoleWindow.h
 * @brief	コンソールウィンドウクラス定義
 * @author	morimoto
 */
#ifndef LIB_DEBUGGER_CONSOLEWINDOW_H
#define LIB_DEBUGGER_CONSOLEWINDOW_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>


namespace Lib
{
	namespace Debugger
	{
		/**
		 * コンソールウィンドウクラス
		 */
		class ConsoleWindow
		{
		public:
			static const int m_OutputBufferSize;	//!< 一度に出力できるバッファのサイズ.

			/**
			 * コンストラクタ
			 */
			ConsoleWindow();

			/**
			 * デストラクタ
			 */
			~ConsoleWindow();

			/**
			 * 初期化処理
			 * @param[in] _windowParam ウィンドウのパラメータ
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool Initialize(LPCTSTR _windowParam);

			/**
			 * 終了処理
			 */
			void Finalize();

			/**
			 * コンソール出力処理
			 * @param[in] _pStr 出力する文字列
			 */
			void Print(TCHAR* _pStr, ...);

		private:
			HANDLE m_ReadHandle;		//!< 読み込みハンドル.
			HANDLE m_WriteHandle;		//!< 書き込みハンドル.
			HANDLE m_ProcessHandle;		//!< プロセスハンドル.

			bool m_IsActive;			//!< コンソールウィンドウがアクティブかのフラグ.

		};
	}
}


#endif // !LIB_DEBUGGER_CONSOLEWINDOW_H
