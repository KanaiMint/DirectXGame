#include "Enemy.h"
#include"GameScene.h"
Enemy::~Enemy() {

	/*for (EnemyBullet* bullet : bullets_) {
	    delete bullet;
	}*/
}

void Enemy::Initialize(Model* model, Vector3 pos) {
	textureHandle_ = TextureManager::Load("kuppa.jpg");
	textureHandle2_ = TextureManager::Load("RED.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	bullets_cooltime = 60;
	/*for (EnemyBullet* bullet : bullets_) {

	    bullet->Initialize(model, worldTransform_.translation_, {});
	}*/
	ApproachInitialize();

	// 衝突判定を設定
	SetcollisionAttribute(kCollisionAttributeEnemy);
	// 衝突対象を自分の属性以外に設定
	uint32_t test = ~kCollisionAttributeEnemy;
	(void)test;
	SetcollisionMask(~kCollisionAttributeEnemy);
	//Fire();
	SetMask(Mask::enemy);
}

void Enemy::Update() {
	if (isDameged) {
		Damagetime -= 0.1f;
		if (Damagetime <= 0) {
			isDameged = false;
		}

	}
	if (Damagetime > 0) {
		isDameged = true;
	}
	////ですフラグの立った球の削除
	// bullets_.remove_if([](EnemyBullet* bullet) {
	//	if (bullet->IsDead() == true) {
	//		delete bullet;
	//		return true;
	//	}
	//	return false;
	// });

	worldTransform_.UpdateMatrix();
	/*for (EnemyBullet* bullet : bullets_) {
	    bullet->Update();
	}*/
	switch (phese_) {
	case Phese::Approach:
	default:
		Approach();
		break;

	case Phese::Leave:
		// 移動（ベクトル加算)
		worldTransform_.translation_ += {0.2f, 0.15f, 0.0f};
		break;
	}
	if (HP <= 0) {
		isDead_ = true;
		player_->ScoreUp();
	}
}

void Enemy::Approach() {
	// 移動（ヴェクトルを加算）
	worldTransform_.translation_ -= MoveSpeed;
	// 弾県警
	bullets_cooltime--;
	if (bullets_cooltime == 0) {
		Fire();
		bullets_cooltime = kbullets_Interval;
	}

	// 規定の位置に達したら離脱
	if (worldTransform_.translation_.z < 5.0f) {
		phese_ = Phese::Leave;
	}
}

void Enemy::Draw(ViewProjection viewProjection) {
	if (!isDameged) {
		model_->Draw(worldTransform_, viewProjection);
	}
	if (isDameged) {
		model_->Draw(worldTransform_, viewProjection, textureHandle2_);	
	}
	//  // 敵弾描画
	//  for (EnemyBullet* bullet : bullets_) {
	// bullet->Draw(viewProjection);
	//  }
}

void Enemy::Fire() {
	// 弾の速度
	const float kEnemyBulletSpeed = 1.0f;
	// Vector3 velocity(0, 0, kEnemyBulletSpeed);
	/*Vector3 PlayerPos = player_->GetWorldPosition();*/
	Vector3 EnemyPos = GetWorldPosition();
	Vector3 PEVec = (player_->MatWorldPlayerPos() - EnemyPos);
	Vector3 velocity = Vector3::Normalize(PEVec);
	velocity.Length({kEnemyBulletSpeed, kEnemyBulletSpeed, kEnemyBulletSpeed});

	// 弾の生成、初期化
	Model* modelcube = nullptr;
	modelcube = Model::Create();
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->SetPlayer(player_);
	newBullet->Initialize(modelcube, worldTransform_.translation_, velocity);
	newBullet->SetGameScene(gameScene_);
	//bullets_.push_back(newBullet);
	gameScene_->AddEnemyBullet(newBullet);
}

void Enemy::ApproachInitialize() { bullets_cooltime = kbullets_Interval; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return Vector3(worldPos);
}

void Enemy::OnCollision(float damage) {
	if (damage > 4.5f) {
		isDead_ = true;
		player_->ScoreUp();
	} else {

		HP -= damage;
		Damagetime = 1.0f;
	}
}
void Enemy::OnCollision2(float damage) {
	/*HP -= 1;
	Damagetime = 1.0f;*/
	damage = damage;
}
