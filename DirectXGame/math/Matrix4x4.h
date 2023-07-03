#pragma once
//#include<Novice.h>
#include"Vector3.h"
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];
};

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 Transpose(const Matrix4x4& m);
Matrix4x4 MakeIdentity4x4();
//平行移動
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
//拡大縮小
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
//座標返還
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);

// x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);
// y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);
// z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);
//ALL回転軸合成
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);

//3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);
static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix,const char*label);
