/**
 * @file	EventListener.h
 * @brief	イベント受信クラス定義
 * @author	morimoto
 */
#ifndef LIB_EVENTLISTENER_H
#define LIB_EVENTLISTENER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <functional>


namespace Lib
{
	class EventBase;

	/*** イベント受信クラス */
	class EventListener final
	{
	public:
		/*** 受信関数オブジェクト */
		using ReceiveFunc = std::function<void(EventBase*)>;

		/**
		 * コンストラクタ
		 * @param[in] _pFunc 設定するイベント受信関数オブジェクト
		 */
		EventListener(ReceiveFunc* _pFunc);

		/*** デストラクタ */
		~EventListener();

		/**
		 * イベントメッセージを受け取る関数
		 * @param[in] _pEvent 受け取るイベントメッセージ
		 */
		void ReceiveEvent(EventBase* _pEvent);
		
		/**
		 * EventListenerのIDを取得する関数
		 * @return EventListenerのID
		 */
		unsigned int GetEventListenerID() const { return m_EventListenerID; }

		/**
		 * イベントの通知を受け取る関数を設定
		 * @param[in] _pFunc 設定する関数ポインタオブジェクト
		 */
		void SetReceiveFunc(ReceiveFunc* _pFunc) { m_pReceiveFunc = _pFunc; }

	private:
		static unsigned int	m_EventListenerCount;	//!< リスナーオブジェクトの作成数.
		unsigned int		m_EventListenerID;		//!< リスナオブジェクトのユニークID.
		ReceiveFunc*		m_pReceiveFunc;			//!< 受信関数ポインタオブジェクト.

	};
}


#endif // !LIB_EVENTLISTENER_H
