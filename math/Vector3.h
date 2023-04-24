#pragma once
#include<cmath>


/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	//加算
	static Vector3 Add(const Vector3& v1, const Vector3& v2);
	//減算
	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);
	//スカラー算
	static Vector3 Multiply(float scalar, const Vector3& v);
	//内積
	static float Dot(const Vector3& v1, const Vector3& v2);
	//長さ(ノルム)
	static float Length(const Vector3& v);
	//正規化
	static Vector3 Normalize(const Vector3& v);

	Vector3& operator+=(const Vector3& other);
};

static const int kColumWidth = 60;

 