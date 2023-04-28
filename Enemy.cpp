#include "Enemy.h"

void Enemy::Initialize(Model* model) 
{ 
	textureHandle_ = TextureManager::Load("black.jpeg");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0, 2, 10};
}     


void Enemy::Update() 
{ 
	worldTransform_.UpdateMatrix();
	
	switch (phese_) {
		case Phese::Approach:
	default:
		    Approach();
		break;

		case Phese::Leave:
			//移動（ベクトル加算)
		worldTransform_.translation_ += {0.2f, 0.15f, 0.0f};
		break;
	}
}

void Enemy::Approach() {
	    // 移動（ヴェクトルを加算）
	    worldTransform_.translation_ -= MoveSpeed;
	    // 規定の位置に達したら離脱
	    if (worldTransform_.translation_.z < -30.0f) {
		phese_ = Phese::Leave;
	    }
}

void Enemy::Draw(ViewProjection viewProjection) 
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
