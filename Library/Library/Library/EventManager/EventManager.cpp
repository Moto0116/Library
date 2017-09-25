/**
 * @file	EventManager.cpp
 * @brief	イベント管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventManager.h"

#include "EventListener\EventListener.h"

#include <algorithm>


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EventManager::EventManager()
	{
	}

	EventManager::~EventManager()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void EventManager::AddEventListener(EventListener* _pEventListener, LPCTSTR _groupName)
	{
		m_pEventListeners[_groupName].push_back(_pEventListener);
	}

	void EventManager::RemoveEventListener(EventListener* _pEventListener, LPCTSTR _groupName)
	{
		auto EventListener = m_pEventListeners[_groupName];

		EventListener.erase(
			std::remove(EventListener.begin(), EventListener.end(), _pEventListener),
			EventListener.end());
	}

	void EventManager::SendEventMessage(EventBase* _pEvent, LPCTSTR _groupName)
	{
		auto EventListener = m_pEventListeners[_groupName];

		for (auto itr = EventListener.begin(); itr != EventListener.end(); itr++)
		{
			(*itr)->EventMessage(_pEvent);
		}
	}
}

