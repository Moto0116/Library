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


namespace Lib
{
	/*** バイナリファイルクラス */
	class BinaryFile
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _pFileName 読み込むファイル名
		 */
		BinaryFile(TCHAR* _pFileName);

		/*** デストラクタ */
		~BinaryFile();

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
		/**
		 * ファイルを読み込む
		 * @param[in] _pFileName 読み込むファイル名
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool LoadFile(TCHAR* _pFileName);

		/*** ファイルを解放 */
		void UnLoadFile();

		void*	m_pBinary;		//!< バイナリの生データ.
		size_t	m_BinarySize;	//!< バイナリデータサイズ.

	};
}


#endif // !BINARYFILE_H
