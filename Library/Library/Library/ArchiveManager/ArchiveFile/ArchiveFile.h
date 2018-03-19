/**
 * @file	ArchiveFile.h
 * @brief	アーカイブファイルクラス定義
 * @author	morimoto
 */
#ifndef LIB_ARCHIVEFILE_H
#define LIB_ARCHIVEFILE_H

namespace Game
{
	/*** アーカイブファイルクラス */
	class ArchiveFile
	{
	public:
		/*** コンストラクタ */
		ArchiveFile();

		/*** デストラクタ */
		~ArchiveFile();

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
		/*** ファイル情報構造体 */
		struct FILE_INFO
		{
			FILE_INFO* pPrev;
			FILE_INFO* pNext;
			void*	pBinary;
			size_t	Size;
		};

		static const size_t m_FileHeaderSize;	//!< アーカイブファイルのヘッダサイズ(byte).

		void*	m_pBinary;		//!< バイナリの生データ.
		size_t	m_BinarySize;	//!< バイナリデータサイズ.

		///@todo マップでFILE_INFOを管理する.

	};
}


#endif // !LIB_ARCHIVEFILE_H
