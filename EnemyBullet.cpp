#include "EnemyBullet.h"
#include"assert.h"
EnemyBullet::~EnemyBullet() {}

	void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& vel) {
		assert(model);
		textureHandle_ = TextureManager::Load("pink.jpg");
		model_ = model;
		worldTransform_.Initialize();
		worldTransform_.translation_ = position;
	    velocity_ = vel;
		//あ
	}

	void EnemyBullet::Update() {

		worldTransform_.UpdateMatrix(); 
		//worldTransform_.translation_ += velocity_;
	    worldTransform_.translation_ += velocity_;
	    if (--deathTimer == 0) {
		    isDead_ = true;
		}
	}

	void EnemyBullet::Draw(ViewProjection & viewProjevtion) {
		model_->Draw(worldTransform_, viewProjevtion,textureHandle_);
		
	}
