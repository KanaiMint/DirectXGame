#include "PlayerBullet.h"
#include"assert.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model); 

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.jpeg");

	worldTransform_.Initialize();
	//因数で受け取った初期座標をセット	
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void PlayerBullet::Update() 
{
	worldTransform_.UpdateMatrix();
	//座標を移動させる（１フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;
	//時間経過でです
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	


}
