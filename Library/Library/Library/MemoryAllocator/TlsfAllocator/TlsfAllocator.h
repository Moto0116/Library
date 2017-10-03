/**
 * @file	TlsfAllocator.h
 * @brief	TLSFメモリアロケータクラス定義
 * @author	morimoto
 */
#ifndef LIB_TLSFALLOCATOR_H
#define LIB_TLSFALLOCATOR_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>


namespace Lib
{
	/**
	 * 境界タグクラス
	 */
	class BoundaryTag
	{
	public:
		BoundaryTag(){}
		~BoundaryTag(){}

		/**
		 * 占有しているメモリのサイズ
		 * @return 占有メモリサイズ
		 */
		size_t GetAllSize()
		{
			return *m_pEndTag;
		}

		/**
		 * 管理しているメモリブロックサイズ
		 * @return 管理しているメモリサイズ
		 */
		size_t GetBlockSize()
		{
			return m_Size;
		}

		/**
		 * 境界タグをリストに追加する
		 * @param[in,out] リストに追加するために使用する境界タグ
		 */
		void AddToList(BoundaryTag* _pTag)
		{
			_pTag->m_pNext = m_pNext;
			_pTag->m_pPrev = this;

			m_pNext = _pTag;
			_pTag->m_pNext->m_pPrev = _pTag;
		}

		/**
		 * 境界タグをリストから削除する
		 */
		BoundaryTag* RemoveFromList()
		{
			m_pPrev->m_pNext = m_pNext;
			m_pNext->m_pPrev = m_pPrev;

			m_pPrev = this;
			m_pNext = this;

			return this;
		}

	private:
		BYTE	m_IsUse;	//!< 使用しているかのフラグ.
		size_t	m_Size;		//!< メモリブロックサイズ.
		BYTE*	m_pBlock;	//!< メモリブロックの先頭ポインタ.
		size_t* m_pEndTag;	//!< 終端タグへのポインタ.

		BoundaryTag* m_pPrev;	//!< 前のタグ.
		BoundaryTag* m_pNext;	//!< 次のタグ.

	};

	/**
	 * TLSFメモリアロケータクラス
	 */
	class TlsfAllocator
	{
	public:
		/**
		 * コンストラクタ
		 */
		TlsfAllocator();

		/**
		 * デストラクタ
		 */
		~TlsfAllocator();

	private:
		void* m_MemoryPool;	//!< メモリプール.

	};
}


#endif // !LIB_TLSFALLOCATOR_H
