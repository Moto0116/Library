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
		/*** デバッグ用タイマークラス */
		class DebugTimer
		{
		public:
			/*** コンストラクタ */
			DebugTimer() : 
				m_DiffTime(0)
			{}

			/*** デストラクタ */
			~DebugTimer() {}

			/*** 計測開始 */
			void StartTimer()
			{
#ifdef _DEBUG
				m_StartTime = std::chrono::system_clock::now();
#endif // _DEBUG
			}

			/*** 計測終了 */
			void EndTimer()
			{
#ifdef _DEBUG
				m_DiffTime = std::chrono::system_clock::now() - m_StartTime;
#endif // _DEBUG
			}

			/**
			 * 計測時間取得
			 * @return 計測時間(Seconds)
			 */
			LONGLONG GetSecond()
			{
				return std::chrono::duration_cast<std::chrono::seconds>(m_DiffTime).count();
			}

			/**
			 * 計測時間取得
			 * @return 計測時間(MilliSeconds)
			 */
			LONGLONG GetMilliSecond()
			{
				return std::chrono::duration_cast<std::chrono::milliseconds>(m_DiffTime).count();
			}

			/**
			 * 計測時間取得
			 * @return 計測時間(MicroSeconds)
			 */
			LONGLONG GetMicroSecond()
			{
				return std::chrono::duration_cast<std::chrono::microseconds>(m_DiffTime).count();
			}

		private:
			using SystemClock	= std::chrono::system_clock;
			using StartTime		= SystemClock::time_point;
			using DebugDiffTime = std::chrono::duration<SystemClock::rep, SystemClock::period>;

			StartTime		m_StartTime;	//!< 計測開始時間.
			DebugDiffTime	m_DiffTime;		//!< 計測時間.

		};
	}
}


#endif // !LIB_DEBUGGER_DEBUGTIMER_H
