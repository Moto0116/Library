/**
 * @file	BinaryFile.cpp
 * @brief	バイナリファイルクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "BinaryFile.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	BinaryFile::BinaryFile(TCHAR* _pFileName) :
		m_pBinary(nullptr),
		m_BinarySize(0)
	{
		bool Result = LoadFile(_pFileName);
		MyAssert(Result == false, "ファイルの読み込みに失敗しました");
	}

	BinaryFile::~BinaryFile()
	{
		UnLoadFile();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	bool BinaryFile::LoadFile(TCHAR* _pFileName)
	{
		MyAssert(m_pBinary != nullptr, "既にファイルが読み込まれています");

		HANDLE FileHandle = CreateFile(
			_pFileName, 
			GENERIC_READ, 
			0, 
			nullptr,
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL,
			nullptr);

		if (FileHandle == INVALID_HANDLE_VALUE)
		{
			OutputErrorLog("ファイルオープンに失敗しました");
			return false;
		}

		m_BinarySize = GetFileSize(FileHandle, nullptr);
		if (m_BinarySize == 0)
		{
			OutputErrorLog("ファイルサイズが0でした");
			CloseHandle(FileHandle);
			return false;
		}

		m_pBinary = malloc(m_BinarySize);
		DWORD ReadSize;
		if (!ReadFile(FileHandle, m_pBinary, m_BinarySize, &ReadSize, nullptr))
		{
			OutputErrorLog("ファイルの読み込み処理に失敗しました");
			CloseHandle(FileHandle);
			return false;
		}

		CloseHandle(FileHandle);

		return true;
	}

	void BinaryFile::UnLoadFile()
	{
		if (m_pBinary != nullptr)
		{
			free(m_pBinary);
			m_pBinary = nullptr;
			m_BinarySize = 0;
		}
	}
}
