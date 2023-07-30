#include "PlayerBullet.h"
#include"assert.h"

void PlayerBullet::Initialize(
    Model* model, const Vector3& position, const Vector3& velocity, bool isharfwindow) {
	assert(model); 

	model_ = model;
	if (isharfwindow) {
		textureHandle_ = TextureManager::Load("Greentex.jpeg");
	}
	if (!isharfwindow) {
		textureHandle_ = TextureManager::Load("black.jpeg");	
	}
	//テクスチャ読み込み

	worldTransform_.Initialize();
	//因数で受け取った初期座標をセット	
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	isHarfUpWindow = isharfwindow;
	// 衝突判定を設定
	SetcollisionAttribute(kCollisionAttributePlayer);
	// 衝突対象を自分の属性以外に設定
	SetcollisionMask(~kCollisionAttributePlayer);
	if (isHarfUpWindow ) {
		SetMask(Mask::playerbullet);
	}
	if (!isHarfUpWindow) {
		SetMask(Mask::playerbulletIsUp);
	}
}

void PlayerBullet::Initialize(
    Model* model, const Vector3& position, const Vector3& velocity, bool isharfwindow,
    float radius,Vector3 scale) 
{
	assert(model);

	model_ = model;
	if (isharfwindow) {
		textureHandle_ = TextureManager::Load("Greentex.jpeg");
	}
	if (!isharfwindow) {
		textureHandle_ = TextureManager::Load("black.jpeg");
	}
	// テクスチャ読み込み

	worldTransform_.Initialize();
	// 因数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	isHarfUpWindow = isharfwindow;
	// 衝突判定を設定
	SetcollisionAttribute(kCollisionAttributePlayer);
	// 衝突対象を自分の属性以外に設定
	SetcollisionMask(~kCollisionAttributePlayer);
	if (isHarfUpWindow) {
		SetMask(Mask::playerbullet);
	}
	if (!isHarfUpWindow) {
		SetMask(Mask::playerbulletIsUp);
	}
	Radius = radius;
	worldTransform_.scale_ = scale;
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
	Setradius(Radius);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	


}

void PlayerBullet::OnCollision(float damage) {
	if (Radius>4.0f) {
		damage = damage;
	
	} else {
	isDead_ = true;
	}
}

void PlayerBullet::OnCollision2(float damage) { 
	isDead_ = true; 
	damage = damage;
}
