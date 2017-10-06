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
#include "Define\Define.h"
#include "Debugger\Debugger.h"
#include "Math\Math.h"

#include <math.h>
#include <new>


namespace Lib
{
	/**
	 * 境界タグクラス
	 */
	class BoundaryTag
	{
	public:
		/**
		 * コンストラクタ
		 */
		BoundaryTag() : 
			m_IsUse(false),
			m_Size(0),
			m_pBlock(nullptr),
			m_pEndTag(nullptr),
			m_pPrev(this),
			m_pNext(this)
		{}

		/**
		 * コンストラクタ
		 * @param[in,out] _pBlock メモリブロックの先頭ポインタ
		 * @param[in] _size メモリブロックサイズ
		 */
		BoundaryTag(BYTE* _pBlock, size_t _size) : 
			m_IsUse(false),
			m_Size(_size),
			m_pBlock(_pBlock),
			m_pEndTag(nullptr),
			m_pPrev(this),
			m_pNext(this)
		{
			if (m_pBlock != nullptr)
			{
				// 終端タグへのポインタを設定.
				m_pEndTag = reinterpret_cast<size_t*>(m_pBlock + m_Size);

				*m_pEndTag =
					sizeof(BoundaryTag) +	// 境界タグ.
					m_Size +				// メモリブロック.
					sizeof(size_t);			// 終端タグ.
			}
		}

		/**
		 * デストラクタ
		 */
		~BoundaryTag()
		{}

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
		TlsfAllocator() : 
			m_pMemory(nullptr),
			m_pFreeList(nullptr)
		{}

		/**
		 * デストラクタ
		 */
		~TlsfAllocator()
		{}

		/**
		 * 初期化処理
		 * @param[in] _memorySize 確保する領域サイズ
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool Initialize(size_t _memorySize)
		{
			m_BoundaryTagSize = sizeof(BoundaryTag);				// 境界タグサイズ記録.
			m_AllTagSize = sizeof(BoundaryTag) + sizeof(size_t);	// 境界タグ+終端タグ記録.

			// 確保領域サイズが2のべき乗の場合を考慮して-1.
			m_MemoryPoolSize = 
				static_cast<size_t>(pow(2.0f, (BitMSB(_memorySize - 1) + 1)));

			// 管理領域分のサイズ記録.
			m_AllSize =
				m_MemoryPoolSize +
				m_AllTagSize * m_DivisionNum +
				m_AllTagSize;

			// メモリ領域の生成と初期化.
			m_pMemory = new BYTE[m_AllSize];
			ZeroMemory(m_pMemory, m_AllSize);

			//初期チャンクのFLIとSLI.
			BYTE FLI = GetFLI(m_AllSize);
			BYTE SLI = GetSLI(m_AllSize, FLI);

			// ブロックリストの領域確保.
			BYTE BlockListNum = FLI * m_DivisionNum + SLI;
			m_pFreeList = new BoundaryTag[BlockListNum];

			// フラグの領域確保と初期化.
			m_FreeListBitFLI = 0;
			m_pFreeListBitSLI = new BYTE[FLI + 1];
			ZeroMemory(m_pFreeListBitSLI,sizeof(BYTE) * (FLI + 1));

			m_pFreeListBit = new BYTE[BlockListNum];
			ZeroMemory(m_pFreeListBit, sizeof(BYTE) * BlockListNum);

			// 最初のメモリブロックタグ生成.
			BoundaryTag* pTag = new(m_pMemory)BoundaryTag(
				reinterpret_cast<BYTE*>(m_pMemory) + m_BoundaryTagSize,
				m_MemoryPoolSize - m_BoundaryTagSize);
			m_pFreeList[BlockListNum - 1].AddToList(pTag);
			m_pFreeListBit[BlockListNum - 1] = 1;
			m_FreeListBitFLI = 1 << FLI;
			m_pFreeListBitSLI[FLI] = 1 << SLI;

			return true;
		}

		/**
		 * 終了処理
		 */
		void Finalize()
		{
			// リストビットフラグの破棄.
			delete[] m_pFreeListBit;
			m_pFreeListBit = nullptr;
			delete[] m_pFreeListBitSLI;
			m_pFreeListBitSLI = nullptr;

			// リストの破棄.
			delete[] m_pFreeList;
			m_pFreeList = nullptr;

			// メモリ領域の破棄.
			delete[] m_pMemory;
			m_pMemory = nullptr;
		}

		/**
		 * メモリの割り当て
		 * @tparam Type 割り当てを行うメモリの型
		 * @return 割り当てたメモリ
		 */
		template<typename Type>
		Type* Allocate()
		{
			size_t MaxFLI = GetFLI(m_AllSize);	///@todo 定数にしておきたい.

			// 要求サイズのFLIとSLIを取得.
			size_t FLI = GetFLI(sizeof(Type) + m_AllTagSize);
			size_t SLI = GetSLI(sizeof(Type) + m_AllTagSize, FLI);
			MyAssert(0 > FLI || FLI > MaxFLI, "FLIが既定のサイズに収まっていません");
			MyAssert(0 > SLI || SLI >= m_DivisionNum, "SLIが既定のサイズに収まっていません");

			// FLIとSLIからFreeIndexを取得してフリーブロックがあるかチェック.
			BYTE FreeIndex = GetFreeIndex(FLI, SLI);
			if (!m_pFreeListBit[FreeIndex])
			{
				// フリーブロックがなければ上位のフリーブロックを取得する.
				SLI = GetFreeListUpSLI(FLI, SLI);
				if (0 <= SLI && SLI < m_DivisionNum)
				{
					// 上位SLIがあった場合.
					FreeIndex = GetFreeIndex(FLI, SLI);
				}
				else
				{
					// 上位SLIがなかった場合.
					FLI = GetFreeListUpFLI(FLI);
					SLI = GetFreeListUpSLI(FLI, 0);
					FreeIndex = GetFreeIndex(FLI, SLI);
				}

				MyAssert(0 > FLI || FLI > MaxFLI, "FLIが既定のサイズに収まっていません");
				MyAssert(0 > SLI || SLI >= m_DivisionNum, "SLIが既定のサイズに収まっていません");
			}

			MyAssert(!m_pFreeListBit[FreeIndex], "フリーリストが使用できる状態ではありません");
			MyAssert(&m_pFreeList[FreeIndex] == m_pFreeList[FreeIndex].m_pNext, "フリーリストの状態が不正です");

			// フリーリストの取得.
			BoundaryTag* pTag = m_pFreeList[FreeIndex].m_pNext;
			MyAssert(sizeof(Type) + m_AllTagSize >= pTag->GetAllSize(), "フリーリストのサイズが小さいです");

			///@todo ここが怪しい.
			//// フリーリストのビット管理.
			//if (m_pFreeList[FreeIndex].m_pNext == &m_pFreeList[FreeIndex])
			//{
			//	m_pFreeListBit[FreeIndex] = 0;
			//	m_pFreeListBitSLI[FLI] &= ~(1 << SLI);
			//	if (m_pFreeListBitSLI[FLI] == 0)	m_FreeListBitFLI &= ~(1 << FLI);
			//}

			/// フリーブロックの分割チェック.
			if ((pTag->GetAllSize() - (sizeof(Type) + m_AllTagSize)) > m_AllTagSize)
			{
				BYTE* pNextTagPos =
					reinterpret_cast<BYTE*>(pTag)+
					pTag->GetAllSize() - sizeof(Type) - m_AllTagSize;

				BoundaryTag* pNextTag = 
					new(pNextTagPos)BoundaryTag(pNextTagPos + m_BoundaryTagSize, sizeof(Type));

				// 新たに作成された境界タグにデータを書き込む.
				pTag->m_Size -= (pNextTag->GetBlockSize() + m_AllTagSize);
				pTag->m_pEndTag = reinterpret_cast<size_t*>(
					pTag->m_pBlock + pTag->GetBlockSize());
				*pTag->m_pEndTag = m_AllTagSize + pTag->GetBlockSize();
				
				MyAssert(pTag->GetBlockSize() > m_MemoryPoolSize, 
					"境界タグが管理するメモリサイズがプールサイズを上回っています");

				// 使用フラグを更新.
				pNextTag->m_IsUse = 1;

				FLI = GetFLI(pTag->GetAllSize());
				SLI = GetSLI(pTag->GetAllSize(), FLI);
				FreeIndex = GetFreeIndex(FLI, SLI);

				MyAssert(0 > FLI || FLI > MaxFLI, "FLIが既定のサイズに収まっていません");
				MyAssert(0 > SLI || SLI >= m_DivisionNum, "SLIが既定のサイズに収まっていません");

				m_pFreeList[FreeIndex].AddToList(pTag);
				pTag->m_IsUse = 0;
				m_pFreeListBit[FreeIndex] = 1;

				m_pFreeListBitSLI[FLI] |= (1 << SLI);
				m_FreeListBitFLI |= (1 << FLI);

				// ブロックの分割を行った際にフラグを変更するべきでは?.

				return reinterpret_cast<Type*>(pNextTag->m_pBlock);
			}

			pTag->m_IsUse = true;

			return reinterpret_cast<Type*>(pTag->m_pBlock);
		}

		/**
		 * メモリの解放
		 * @tparam Type 解放するメモリの型
		 * @param[in,out] _p 解放するメモリ 
		 */
		template<typename Type>
		void DeAllocate(Type* _p)
		{
			// 前後のデータ参照を行う.
			BoundaryTag* pPrevTag;
			BoundaryTag* pTag;
			BoundaryTag* pNextTag;
			BYTE* pPrevData;
			BYTE* pData;
			BYTE* pNextData;
			size_t* pPrevEndTag;
			size_t* pEndTag;
			size_t* pNextEndTag;

			pData = reinterpret_cast<BYTE*>(_p);
			pTag = reinterpret_cast<Lib::BoundaryTag*>(pData - m_BoundaryTagSize);
			pEndTag = reinterpret_cast<size_t*>(pData + sizeof(Type));

			///@todo 前後関係のチェック.
			///@todo メモリの整合性のチェック.
			///@todo マージのチェック.
		}

		/**
		 * ビット列からFLIを取得
		 * @param[in] _bits ビット列
		 * @return FLI
		 */
		__forceinline BYTE GetFLI(size_t _bits)
		{
			if (_bits == 0) return 0;
			_bits -= 1;
			_bits |= (_bits >> 1);
			_bits |= (_bits >> 2);
			_bits |= (_bits >> 4);
			_bits |= (_bits >> 8);
			_bits |= (_bits >> 16);
			return BitCount(_bits) - 1;	// 0起点なので-1で調整.
		}

		/**
		 * ビット列とFLIからSLIを取得
		 * @param[in] _bits ビット列
		 * @param[in] _fli FLI
		 * @return SLI
		 */
		__forceinline BYTE GetSLI(size_t _bits, BYTE _fli)
		{
			/// @todo 要検証.
			_bits -= 1;
			size_t Mask = ~(0xffffffff << _fli);
			return (_bits & Mask) >> (_fli - m_DivisionRate);
		}

		/**
		 * FLIとSLIからフリーリストのインデックスを取得
		 * @param[in] _fli FLI
		 * @param[in] _sli SLI
		 * @return フリーリストのインデックス
		 */
		__forceinline BYTE GetFreeIndex(BYTE _fli, BYTE _sli)
		{
			return _fli * m_DivisionNum + _sli - 1;
		}

		/**
		 * 上位FLIを取得
		 * @param[in] _fli FLI
		 * @return 上位FLI(なければ-1を返す)
		 */
		__forceinline BYTE GetFreeListUpFLI(BYTE _fli)
		{
			size_t Mask = 0xffffffff << _fli;		// FLI以上を立たせたマスク値.
			size_t Bits = m_FreeListBitFLI & Mask;
			if (Bits == 0)	return -1;

			return BitLSB(Bits);	// 最小bitを返す.
		}

		/**
		 * 同じFLI内から上位SLIを取得
		 * @param[in] _fli FLI
		 * @param[in] _sli SLI
		 * @return 上位SLI(なければ-1を返す)
		 */
		__forceinline BYTE GetFreeListUpSLI(BYTE _fli, BYTE _sli)
		{
			BYTE Mask = 0xffffffff << _sli;				// SLI以上を立たせたマスク値.
			BYTE Bits = m_pFreeListBitSLI[_fli] & Mask;
			if (Bits == 0)	return -1;

			return BitLSB(Bits);	// 最小bitを返す.
		}

	private:
		static const int m_DivisionNum = 4;		//!< メモリ分割数.
		static const int m_DivisionRate = 2;	//!< 2^m_DevisionRate = m_DivisionNum.

		void* m_pMemory;	//!< メモリの先頭ポインタ.

		BoundaryTag* m_pFreeList;	//!< フリーリストブロック.

		size_t m_FreeListBitFLI;	//!< フリーリストビットのFLI.
		BYTE* m_pFreeListBitSLI;	//!< フリーリストビットのSLI.

		BYTE* m_pFreeListBit;		//!< フリーリストブロックが存在するかのフラグ.

		size_t m_MemoryPoolSize;	//!< メモリプールのサイズ.
		size_t m_AllSize;			//!< メモリプールと管理領域を含めたサイズ.

		size_t m_BoundaryTagSize;	//!< 境界タグサイズ(今のところ変数として持つ).
		size_t m_AllTagSize;		//!< 境界タグと終端タグを合わせたサイズ.

	};
}


#endif // !LIB_TLSFALLOCATOR_H
