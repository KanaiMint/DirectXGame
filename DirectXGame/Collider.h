#pragma once
#include "Vector3.h"
class Collider {

private:
	//衝突半径	
	float radius_ = 1.0f;

public:

	//半径を取得
	float Getradius() { return radius_; }
	void Setradius(float rad) { radius_ = rad; }

	//衝突時に呼ばれる関数
	virtual void OnCollision();
	//ワールド座標を取得
	virtual Vector3 GetWorldPosition() = 0;



};
