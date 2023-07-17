#include "EnemyBullet.h"
#include "assert.h"
#include <cmath>
#include"GameScene.h"

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
	    std::atan2(velocity_.x / velocity_.z, Vector3::Length({velocity_}));
	// あ
	//   衝突判定を設定
	SetcollisionAttribute(kCollisionAttributeEnemy);
	// 衝突対象を自分の属性以外に設定
	SetcollisionMask(~kCollisionAttributeEnemy);
	SetMask(Mask::enemybullet);
}

void EnemyBullet::Update() {

	if (IsReflection == false) {

		// worldTransform_.translation_ += velocity_;
		// 敵弾からジキャラへのベクトルを計算
		// Matrix4x4 playercamerapos = Multiply(player_->GetMatworld(), player_->Getparent());
		Vector3 playermpos = player_->MatWorldPlayerPos();
		/*Vector3(playercamerapos.m[3][0], playercamerapos.m[3][1], playercamerapos.m[3][2])*/;

		Vector3 toPlayer = playermpos - worldTransform_.translation_;
		// 球面線形補間により、今の速度とジキャラのベクトルを内挿し、新たな速度とする
		if (player_->GetMatworld().m[3][3] < worldTransform_.translation_.z)
		{
			//velocity_ = Slerp(velocity_, toPlayer, 0.03f) * kBulletSpeed;
			velocity_ = toPlayer.Normalize(toPlayer) * kBulletSpeed;
		}
		// 弾の角度
		worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
		Matrix4x4 tmp = MakeRotateYMatrix(-std::atan2(velocity_.x, velocity_.z));
		Vector3 velZ = Transform(velocity_, tmp);
		worldTransform_.rotation_.x = std::atan2(-velZ.y, velZ.z);

		
	}
	if (IsReflection == true) {
	
	}


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

void EnemyBullet::Draw(ViewProjection& viewProjevtion) {
	model_->Draw(worldTransform_, viewProjevtion, textureHandle_);
}

void EnemyBullet::OnCollision2() 
{ 	
	//増えるヤツ
	 // 弾の速度
	const float kEnemyBulletSpeed = 1.0f;
	// Vector3 velocity(0, 0, kEnemyBulletSpeed);
	/*Vector3 PlayerPos = player_->GetWorldPosition();*/
	Vector3 EnemyPos = GetWorldPosition();
	Vector3 PEVec = (player_->MatWorldPlayerPos() - EnemyPos);
	Vector3 velocity = Vector3::Normalize(PEVec);
	velocity.Length({kEnemyBulletSpeed, kEnemyBulletSpeed, kEnemyBulletSpeed});

	// 弾の生成、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->SetPlayer(player_);
	newBullet->SetGameScene(gameScene_);
	newBullet->Initialize(model_, worldTransform_.translation_ +Vector3(1.0f,0,0), velocity);
	// bullets_.push_back(newBullet);
	gameScene_->AddEnemyBullet(newBullet);
	//isDead_ = true;
}

void EnemyBullet::OnCollision() {
	//
	if (player_->GetIsReflection() == true) {
		IsReflection = true;
		Vector3 tmp = player_->worldTransform3DReticle_.translation_ - player_->MatWorldPlayerPos();
		;
		velocity_ = Vector3::Normalize(tmp) * kBulletSpeed;
		deathTimer = killTimer;
		// 衝突判定を設定
		SetcollisionAttribute(kCollisionAttributePlayer);
		// 衝突対象を自分の属性以外に設定
		SetcollisionMask(~kCollisionAttributePlayer);
		// isDead_ = true;
	} else {

		isDead_ = true;
	}
}

Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
