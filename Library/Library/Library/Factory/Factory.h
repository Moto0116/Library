/**
 * @file	Factory.h
 * @brief	オブジェクト生成クラス定義
 * @author	morimoto
 */
#ifndef LIB_FACTORY_H
#define LIB_FACTORY_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <map>

#include "..\Define\Define.h"


namespace Lib
{
	/**
	 * オブジェクト生成クラス
	 * @tparam Type 生成するオブジェクト型
	 * @tparam Identifier オブジェクトの識別子
	 */
	template <typename Type, typename Identifier>
	class Factory final
	{
	public:
		using Func = Type*(*)();

		/**
		 * インスタンスの取得
		 * @return インスタンス 
		 */
		static Factory* GetInstance()
		{
			static Factory Instance;
			return &Instance;
		}

		/**
		 * 生成関数登録
		 * @param[in] _pFunction 生成関数
		 * @param[in] _id 識別子
		 * @return 登録に成功したらtrue 失敗したらfalse
		 */
		bool Register(Func _pFunction, Identifier _id);

		/**
		 * 生成関数の登録を解除
		 * @param[in] _id 生成関数の識別子
		 * @return 登録解除に成功したらtrue 失敗したらfalse
		 */
		bool UnRegister(Identifier _id);

		/**
		 * オブジェクトの生成
		 * @param[in] _id 生成関数の識別子
		 * @return 生成オブジェクト
		 */
		Type* Create(Identifier _id);

	private:
		/*** コンストラクタ */
		Factory();

		/*** デストラクタ */
		~Factory();

		std::map<Identifier, Func> m_Functions;	//!< 生成関数のコンテナ.

	};
}


#include "Factory_private.inl"


#endif // !LIB_FACTORY_H
