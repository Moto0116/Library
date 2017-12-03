/**
 * @file	Hash.h
 * @brief	ハッシュ機能定義実装
 * @author	morimoto
 */
#ifndef LIB_HASH_H
#define LIB_HASH_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <stdint.h>


namespace Lib
{
	//----------------------------------------------------------------------
	// Static Global Variables
	//----------------------------------------------------------------------
	static const uint32_t FNV_INIT_32 = 2166136261;
	static const uint64_t FNV_INIT_64 = 14695981039346656037;
	static const uint32_t FNV_PRIME_32 = 16777619;
	static const uint64_t FNV_PRIME_64 = 1099511628211;


	//----------------------------------------------------------------------
	// Global Functions
	//----------------------------------------------------------------------

	/**
	 * FNV-1-32bitハッシュ生成関数
	 * @param[in] _pBytes ハッシュに変換するデータ
	 * @param[in] _length データのサイズ
	 * @return 生成したハッシュ値
	 */
	uint32_t FNV1Hash32(uint8_t* _pBytes, int _length)
	{
		uint32_t Hash = FNV_INIT_32;
		for (int i = 0; i < _length; i++)
			Hash = (FNV_PRIME_32 * Hash) ^ _pBytes[i];

		return Hash;
	}

	/**
	 * FNV-1-64bitハッシュ生成関数
	 * @param[in] _pBytes ハッシュに変換するデータ
	 * @param[in] _length データのサイズ
	 * @return 生成したハッシュ値
	 */
	uint64_t FNV1Hash64(uint8_t* _pBytes, int _length)
	{
		uint64_t Hash = FNV_INIT_64;
		for (int i = 0; i < _length; i++)
			Hash = (FNV_PRIME_64 * Hash) ^ _pBytes[i];

		return Hash;
	}
}

#endif // !LIB_HASH_H
