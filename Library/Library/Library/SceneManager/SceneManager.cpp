﻿/**
 * @file	SceneManager.cpp
 * @brief	シーン管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SceneManager.h"

#include "..\Define\Define.h"
#include "..\Debugger\Debugger.h"
#include "SceneBase\SceneBase.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const int SceneManager::m_EmptySceneID = -1;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SceneManager::SceneManager() :
		m_pCurrentScene(nullptr)
	{
	}

	SceneManager::~SceneManager()
	{
		MyAssert(!m_pScenes.empty(), "登録されたシーンが残っています");

		for (auto itr = m_pScenes.begin(); itr != m_pScenes.end(); itr++)
		{
			SafeDelete(*itr);
		}
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool SceneManager::Initialize()
	{
		SceneBase* pEmptyScene = new SceneBase(m_EmptySceneID);
		m_pScenes.push_back(pEmptyScene);

		m_pCurrentScene = pEmptyScene;	// 空シーンを現在のシーンとして登録しておく.

		return true;
	}

	void SceneManager::Finalize()
	{
		for (auto itr = m_pScenes.begin(); itr != m_pScenes.end(); itr++)
		{
			if ((*itr)->GetID() == m_EmptySceneID)	// 空シーンを探して削除する.
			{
				SafeDelete(*itr);
				m_pScenes.erase(itr);
				break;
			}
		}
	}

	bool SceneManager::Update()
	{
		switch (m_pCurrentScene->GetState())
		{
		case SceneBase::INIT_STATE:
			if (!m_pCurrentScene->Initialize()) return true;

			break;
		case SceneBase::UPDATE_STATE:
			m_pCurrentScene->Update();

			break;
		case SceneBase::FINAL_STATE:
			int NextSceneID = m_pCurrentScene->GetNextSceneID();	// 遷移先のシーンIDを取得する.
			m_pCurrentScene->Finalize();

			for (auto itr = m_pScenes.begin(); itr != m_pScenes.end(); itr++)
			{
				if ((*itr)->GetID() == NextSceneID)
				{
					m_pCurrentScene = (*itr);	// 遷移先を見つけたら現在のシーンに設定.
					return false;
				}
			}

			return true;	// 遷移先が見つからなければ動作を終了する.

			break;
		}

		return false;
	}

	bool SceneManager::AddScene(SceneBase* _pScene)
	{
		for (auto itr = m_pScenes.begin(); itr != m_pScenes.end(); itr++)
		{
			if ((*itr)->GetID() == _pScene->GetID())
			{
				OutputErrorLog("シーンIDがユニークではありません");
				return false;
			}
		}

		m_pScenes.push_back(_pScene);

		return true;
	}

	void SceneManager::DeleteScene(SceneBase* _pScene)
	{
		for (auto itr = m_pScenes.begin(); itr != m_pScenes.end(); itr++)
		{
			if ((*itr)->GetID() == _pScene->GetID())
			{
				switch ((*itr)->GetState())
				{
				case SceneBase::INIT_STATE:
					break;
				case SceneBase::UPDATE_STATE:
					(*itr)->Finalize();	// オブジェクトが生きていれば破棄する.
					break;
				case SceneBase::FINAL_STATE:
					break;
				}

				m_pScenes.erase(itr);
				break;
			}
		}
	}

	void SceneManager::SetEntryScene(SceneBase* _pScene)
	{
		for (auto itr = m_pScenes.begin(); itr != m_pScenes.end(); itr++)
		{
			if ((*itr)->GetID() == _pScene->GetID())
			{
				m_pCurrentScene = (*itr);	// 現在のシーンとして設定.
			}
		}
	}
}

