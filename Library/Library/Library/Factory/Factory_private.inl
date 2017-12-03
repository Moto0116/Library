/**
 * @file	Factory_private.inl
 * @brief	オブジェクト生成クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Factory.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	template <typename Type, typename Identifier>
	inline Factory<Type, Identifier>::Factory()
	{
	}

	template <typename Type, typename Identifier>
	inline Factory<Type, Identifier>::~Factory()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	template <typename Type, typename Identifier>
	inline bool Factory<Type, Identifier>::Register(Func _pFunction, Identifier _id)
	{
		return m_Functions.insert(std::make_pair(_id, _pFunction)).second;
	}

	template <typename Type, typename Identifier>
	inline bool Factory<Type, Identifier>::UnRegister(Identifier _id)
	{
		return m_Functions.erase(_id) == 1;
	}

	template <typename Type, typename Identifier>
	inline Type* Factory<Type, Identifier>::Create(Identifier _id)
	{
		return m_Functions[_id]();
	}
}
