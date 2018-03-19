/**
 * @file	Math.h
 * @brief	算術系関数定義
 * @author	morimoto
 */
#ifndef LIB_MATH_H
#define LIB_MATH_H


//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>
#include "Vector2\Vector2.h"
#include "Vector3\Vector3.h"
#include "Vector4\Vector4.h"
#include "Matrix\Matrix.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Global Variables
	//----------------------------------------------------------------------
	const float g_LibPI = 3.14159265358979323846f;


	//----------------------------------------------------------------------
	// Utility Functions
	//----------------------------------------------------------------------

	/**
	 * 角度をラジアンに変換
	 * @param[in] _degree 角度 
	 * @return ラジアンに変換した角度
	 */
	__forceinline float ToRadian(float _degree)
	{
		return _degree * (g_LibPI / 180.0f);
	}

	/**
	 * ラジアンから角度に変換
	 * @param[in] _radian ラジアン 
	 * @return 角度に変換したラジアン
	 */
	__forceinline float ToDegree(float _radian)
	{
		return _radian * (180.0f / g_LibPI);
	}

	/**
	 * 32bit列の中で立っているbit数を取得
	 * @param[in] _bits チェックするビット列
	 * @return 立っているbit数
	 */
	__forceinline int BitCount(size_t _bits)
	{
		_bits = (_bits & 0x55555555) + (_bits >> 1 & 0x55555555);
		_bits = (_bits & 0x33333333) + (_bits >> 2 & 0x33333333);
		_bits = (_bits & 0x0f0f0f0f) + (_bits >> 4 & 0x0f0f0f0f);
		_bits = (_bits & 0x00ff00ff) + (_bits >> 8 & 0x00ff00ff);
		return (_bits & 0x0000ffff) + (_bits >> 16 & 0x0000ffff);
	}

	/**
	 * 32bit列の中の最大有効bit(MSB)を取得
	 * @param[in] _bits チェックするビット列
	 * @return 最大有効bit
	 */
	__forceinline int BitMSB(size_t _bits)
	{
		if (_bits == 0) return 0;
		_bits |= (_bits >> 1);
		_bits |= (_bits >> 2);
		_bits |= (_bits >> 4);
		_bits |= (_bits >> 8);
		_bits |= (_bits >> 16);
		return BitCount(_bits) - 1;	// 0起点なので-1で調整.
	}

	/**
	 * 32bit列の中の最小有効bit(LSB)を取得
	 * @param[in] _bits チェックするビット列
	 * @return 最小有効bit
	 */
	__forceinline int BitLSB(size_t _bits)
	{
		if (_bits == 0) return 0;
		_bits |= (_bits << 1);
		_bits |= (_bits << 2);
		_bits |= (_bits << 4);
		_bits |= (_bits << 8);
		_bits |= (_bits << 16);
		return 32 - BitCount(_bits);
	}

	/**
	 * 値同士を比較して大きいものを返す
	 * @param[in] 比較する値1
	 * @param[in] 比較する値2
	 */
	template<typename Type>
	__forceinline Type Max(const Type& _in1, const Type& _in2)
	{
		return (_in1 < _in2) ? _in2 : _in1;
	}

	/**
	 * 値同士を比較して小さいものを返す
	 * @param[in] 比較する値1
	 * @param[in] 比較する値2
	 */
	template<typename Type>
	__forceinline Type Min(const Type& _in1, const Type& _in2)
	{
		return (_in1 < _in2) ? _in1 : _in2;
	}


	//----------------------------------------------------------------------
	// Vector Functions
	//----------------------------------------------------------------------
	float Vector3Dot(const VECTOR3* _pIn1, const VECTOR3* _pIn2);
	VECTOR3 Vector3Cross(const VECTOR3* _pIn1, const VECTOR3* _pIn2, VECTOR3* _pOut);
	VECTOR3 Vector3Normalize(VECTOR3* _pOut);
	float VectorLength(const VECTOR2* _pIn);
	float VectorLength(const VECTOR3* _pIn);
	float VectorDistance(const VECTOR2* _pIn1, const VECTOR2* _pIn2);
	float VectorDistance(const VECTOR3* _pIn1, const VECTOR3* _pIn2);
	float VectorRadian(const VECTOR2* _pIn1, const VECTOR2* _pIn2);
	float VectorDegree(const VECTOR2* _pIn1, const VECTOR2* _pIn2);


	//----------------------------------------------------------------------
	// Matrix Functions
	//----------------------------------------------------------------------
	MATRIX MatrixIdentity(MATRIX* _pMat);
	MATRIX MatrixTranspose(MATRIX* _pMat);
	MATRIX MatrixTranslation(MATRIX* _pMat, float _x, float _y, float _z);
	MATRIX MatrixScaling(MATRIX* _pMat, float _x, float _y, float _z);
	MATRIX MatrixRotationX(MATRIX* _pMat, float _angle);
	MATRIX MatrixRotationY(MATRIX* _pMat, float _angle);
	MATRIX MatrixRotationZ(MATRIX* _pMat, float _angle);

	/**
	 * 左手系ビュー行列作成
	 * @param[out] _pMat 行列の出力先
	 * @param[in] _eyePos 視点の座標
	 * @param[in] _at 注視座標
	 * @param[in] _up 上方向
	 * @return 作成した行列
	 */
	MATRIX MatrixLookAtLH(
		MATRIX* _pMat,
		VECTOR3* _pEyePos,
		VECTOR3* _pAt, 
		VECTOR3* _pUp = &VECTOR3(0.f, 1.f, 0.f));

	/**
	 * 左手座標系パースペクティブ射影行列作成
	 * @param[out] _pMat 行列の出力先
	 * @param[in] _fovY Y方向の視野角
	 * @param[in] _aspect アスペクト比
	 * @param[in] _zNear 最近点
	 * @param[in] _zFar 最遠点
	 * @return 作成した行列
	 */
	MATRIX MatrixPerspectiveFovLH(
		MATRIX* _pMat,
		float _fovY, 
		float _aspect,
		float _zNear, 
		float _zFar);

}


#endif // !LIB_MATH_H
