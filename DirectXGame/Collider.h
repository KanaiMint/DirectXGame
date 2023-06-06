#pragma once
#include "Vector3.h"
#include "CollisionConfig.h"
class Collider {

private:
	//衝突半径	
	float radius_ = 1.0f;
	//衝突属性（自分）
	uint32_t collisionAttribute_ = 0xffffffff;
	//衝突マスク(相手)
	uint32_t collisionMask_ = 0xffffffff;

public:

	//半径を取得
	float Getradius() { return radius_; }
	void Setradius(float rad) { radius_ = rad; }

	//衝突時に呼ばれる関数
	virtual void OnCollision();
	//ワールド座標を取得
	virtual Vector3 GetWorldPosition() = 0;

	//衝突属性（自分）を取得
	uint32_t GetcollisionAttribute() { return collisionAttribute_; }
	//衝突属性（自分）を設定
	void SetcollisionAttribute(uint32_t collisionAttribute)
		{collisionAttribute_ = collisionAttribute;}
	//衝突マスク（相手）を取得
	uint32_t GetcollisionMask() { return collisionMask_; }
	//衝突マスク（相手を設定）
	void SetcollisionMask(uint32_t collisionMask) {
		collisionMask_ = collisionMask;
	}

};
