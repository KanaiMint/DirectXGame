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
		worldTransform_.UpdateMatrix(); 

	    worldTransform_.rotation_.x =
	        std::atan2(-velocity_.y, Vector3::Length({velocity_.x, 0.0f, velocity_.z}));

	    worldTransform_.rotation_.y =
	        std::atan2( velocity_.x/velocity_.z,Vector3::Length({velocity_}));
		//あ
	    //  衝突判定を設定
	    SetcollisionAttribute(kCollisionAttributeEnemy);
	    // 衝突対象を自分の属性以外に設定
	    SetcollisionMask(~kCollisionAttributeEnemy);
	}

	void EnemyBullet::Update() {

		//worldTransform_.translation_ += velocity_;
		//敵弾からジキャラへのベクトルを計算
	    Vector3 toPlayer = player_->GetWorldPosition() - worldTransform_.translation_;	   
		//球面線形補間により、今の速度とジキャラのベクトルを内挿し、新たな速度とする
	    velocity_ = Slerp(velocity_, toPlayer, 0.03f) * 0.5f;

	    worldTransform_.rotation_.y =
	        std::atan2(velocity_.x,velocity_.z );
	    Matrix4x4 tmp = MakeRotateYMatrix(-std::atan2(velocity_.x, velocity_.z));
	    Vector3 velZ = Transform(velocity_,tmp);

	    worldTransform_.rotation_.x = std::atan2(-velZ.y,velZ.z);

	    worldTransform_.translation_ += velocity_;
		worldTransform_.UpdateMatrix(); 

	    if (--deathTimer == 0) {
		    isDead_ = true;
		}

		ImGui::Begin("window");
	    // デバックテキスト表示
	    ImGui::Text(
	        "EnemyBullet %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	        worldTransform_.translation_.z);
	    // ImGui::InputFloat3("Player", Inputfloat3);
	    // ImGui::SliderFloat3("Player", Inputfloat3,0.0f,1.0f);
	    ImGui::End();
	}

	void EnemyBullet::Draw(ViewProjection & viewProjevtion) {
		model_->Draw(worldTransform_, viewProjevtion,textureHandle_);
		
	}

    void EnemyBullet::OnCollision() { isDead_ = true; }

    Vector3 EnemyBullet::GetWorldPosition() { return Vector3(worldTransform_.translation_); }
