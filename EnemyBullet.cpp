#include "EnemyBullet.h"
#include"assert.h"
#include<cmath>
EnemyBullet::~EnemyBullet() {}

	void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& vel) {
		assert(model);
		textureHandle_ = TextureManager::Load("pink.jpg");
		model_ = model;
		worldTransform_.Initialize();
		worldTransform_.translation_ = position;
	    worldTransform_.scale_ = {0.5f, 0.5f, 3.0f};
	    velocity_ = vel;


	    worldTransform_.rotation_.x =
	        std::atan2(-velocity_.y, Vector3::Length({velocity_.x, 0.0f, velocity_.z}));

	    worldTransform_.rotation_.y =
	        std::atan2( velocity_.x/velocity_.z,Vector3::Length({velocity_}));
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
