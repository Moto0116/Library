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
	void EventManager::AddEventListener(EventListener* _pEventListener)
	{
		m_pEventListener.push_back(_pEventListener);
	}

	void EventManager::RemoveEventListener(EventListener* _pEventListener)
	{
		m_pEventListener.erase(
			std::remove(m_pEventListener.begin(), m_pEventListener.end(), _pEventListener),
			m_pEventListener.end());
	}

	void EventManager::SendEventMessage(EventBase* _pEvent)
	{
		for (auto itr = m_pEventListener.begin(); itr != m_pEventListener.end(); itr++)
		{
			(*itr)->EventMessage(_pEvent);
		}
	}
}

