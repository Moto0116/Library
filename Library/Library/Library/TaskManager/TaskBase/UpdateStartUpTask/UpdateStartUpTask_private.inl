/**
 * @file	UpdateStartUpTask_private.inl
 * @brief	�X�V�J�n�O�̃^�X�N�N���X����
 * @author	morimoto
 */


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	inline UpdateStartUpTask::UpdateStartUpTask() :
		m_pObject(nullptr)
	{
	}

	inline UpdateStartUpTask::~UpdateStartUpTask()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	inline void UpdateStartUpTask::Run()
	{
		m_pObject->UpdateStartUp();
	}

	inline void UpdateStartUpTask::SetObject(ObjectBase* _pObject)
	{
		m_pObject = _pObject;
	}
}
