/**
 * @file	DebugTimer.h
 * @brief	デバッグ用タイマークラス定義実装
 * @author	morimoto
 */
#ifndef LIB_DEBUGGER_DEBUGTIMER_H
#define LIB_DEBUGGER_DEBUGTIMER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>
#include <chrono>


namespace Lib
{
	namespace Debugger
	{
		/**
		 * デバッグ用タイマークラス
		 */
		class DebugTimer
		{
		public:
			/**
			 * コンストラクタ
			 */
			DebugTimer() : m_DiffTime(0){}

			/**
			 * デストラクタ
			 */
			~DebugTimer(){}

			/**
			 * 計測開始
			 */
			void StartTimer()
			{
#ifdef _DEBUG
				m_StartTime = std::chrono::system_clock::now();
#endif // _DEBUG
			}

			/**
			 * 計測終了
			 */
			void EndTimer()
			{
#ifdef _DEBUG
				m_EndTime = std::chrono::system_clock::now();
				auto Diff = m_EndTime - m_StartTime;
				m_DiffTime = std::chrono::duration_cast<std::chrono::milliseconds>(Diff).count();
#endif // _DEBUG
			}

			/**
			 * 計測時間取得
			 * @return 計測時間(msec単位)
			 */
			LONGLONG GetTime()
			{
				return m_DiffTime;
			}

		private:
			std::chrono::system_clock::time_point	m_StartTime;	//!< 計測開始時間.
			std::chrono::system_clock::time_point	m_EndTime;		//!< 計測終了時間.
			LONGLONG								m_DiffTime;		//!< 計測時間(msec単位).

		};
	}
}


#endif // !LIB_DEBUGGER_DEBUGTIMER_H
