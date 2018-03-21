/**
 * @file	EventManager.h
 * @brief	イベント管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_EVENTMANAGER_H
#define LIB_EVENTMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>
#include <map>

#include "Debugger\Debugger.h"
#include "..\SingletonBase\SingletonBase.h"


namespace Lib
{
	class EventBase;
	class EventListener;

	/*** イベント管理クラス */
	class EventManager final : public SingletonBase<EventManager>
	{
	public:
		friend SingletonBase<EventManager>;

		/**
		 * EventListenerをグループに追加する
		 * @param[in] _pEventListener 追加するイベントリスナ
		 * @param[in] _groupName イベントリスナを追加するグループの名前
		 */
		void AddEventListener(EventListener* _pEventListener, LPCTSTR _groupName);

		/**
		 * EventListenerをグループから削除する
		 * @param[in] _pEventListener 削除するイベントリスナ
		 * @param[in] _groupName イベントリスナを削除するグループの名前
		 */
		void RemoveEventListener(EventListener* _pEventListener, LPCTSTR _groupName);

		/**
		 * イベントをグループに通知する
		 * @param[in] _pEvent 通知するイベント
		 * @param[in] _groupName イベントを通知するグループ名
		 */
		void SendEventMessage(EventBase* _pEvent, LPCTSTR _groupName);

	private:
		/*** LPCTSTR比較用のオブジェクト */
		struct CompareStr
		{
		public:
			bool operator()(LPCTSTR _str1, LPCTSTR _str2) const
			{
				return strcmp(_str1, _str2) < 0;
			}
		};

		/*** コンストラクタ */
		EventManager();

		/*** デストラクタ */
		virtual ~EventManager();

		std::map<
			LPCTSTR,
			std::vector<EventListener*>,
			CompareStr>
			m_pEventListenerGroups;	//!< イベントリスナを格納するコンテナ.

#ifdef _DEBUG
		Debugger::ConsoleWindow		m_ConsoleWindow;	//!< デバッグ情報を出力するウィンドウ.
#endif // _DEBUG
	};
}


#endif // !LIB_EVENTMANAGER_H
