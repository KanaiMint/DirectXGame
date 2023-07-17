#pragma once
#include <cmath>

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {
	float x;
	float y;

	// 長さ(ノルム)
	static float Length(const Vector2& v, const Vector2& v2);
};
