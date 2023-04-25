#include "Enemy.h"

void Enemy::Initialize(Model* model) 
{ 
	textureHandle_ = TextureManager::Load("black.jpeg");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0, 2, 0};
}


void Enemy::Update() 
{ 
	worldTransform_.UpdateMatrix();
	
	worldTransform_.translation_ += {0, 0, -0.2f};
}

void Enemy::Draw(ViewProjection viewProjection) 
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
