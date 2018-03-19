/**
 * @file	BinaryFile.h
 * @brief	バイナリファイルクラス定義
 * @author	morimoto
 */
#ifndef LIB_BINARYFILE_H
#define LIB_BINARYFILE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>

#include "Define\Define.h"


namespace Lib
{
	/*** バイナリファイルクラス */
	class BinaryFile
	{
	public:
		/*** コンストラクタ */
		BinaryFile();

		/*** デストラクタ */
		~BinaryFile();

		/**
		 * ファイルからデータを読み込む
		 * @param[in] _pFileName 読み込むファイル名
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool LoadFromFile(TCHAR* _pFileName);

		/*** データを解放 */
		void UnLoadFile();

		/**
		 * バイナリデータの取得
		 * @return バイナリの生データ
		 */
		void* GetBinary() const	{ return m_pBinary; }

		/**
		 * バイナリデータサイズの取得
		 * @return バイナリデータのサイズ
		 */
		size_t GetBinarySize() const { return m_BinarySize; }

	private:
		void*	m_pBinary;		//!< バイナリの生データ.
		size_t	m_BinarySize;	//!< バイナリデータサイズ.

		DISALLOW_COPY_AND_ASSIGN(BinaryFile);

	};
}


#endif // !BINARYFILE_H
