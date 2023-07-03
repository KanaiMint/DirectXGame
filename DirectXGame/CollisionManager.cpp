#include "CollisionManager.h"

void CollisionManager::Initialize(Player* player /*, Enemy* enemy*/) {

	player_ = player;
	/*enemy_ = enemy;*/
}

void CollisionManager::Update(
    Player* player, std::list<Enemy*>& enemy, std::list<EnemyBullet*>& enemyBullets_) {
	colliders_.clear();
	player_ = player;
	// enemy_ = enemy;
	CheckAllCollision(enemy, enemyBullets_);
}

void CollisionManager::CheckAllCollision(
    std::list<Enemy*>& enemys_, std::list<EnemyBullet*>& enemyBullets_) {
	// 判定対象AとBの座標
	//	Vector3 posA, posB;
	// 自弾リストの取得
	const std::list<PlayerBullet*> playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<EnemyBullet*> enemyBullets = enemyBullets_;
	// 敵リストの取得

	// #pragma region ジキャラと敵弾の当たり判定
	//////ジキャラの座標
	////posA = player_->GetWorldPosition();
	////ジキャラと敵弾すべての当たり判定
	// for (EnemyBullet* bullet : enemyBullets) {
	//
	//	/*posB = bullet->GetWorldPosition();
	//	float distance =
	//	    std::powf(posB.x - posA.x,2.0f) + std::powf(posB.y - posA.y,2.0f) + std::powf(posB.z -
	// posA.z,2.0f);

	//	if (distance <= std::powf(player_->GetRadius() + bullet->GetRadius(),2.0f)) {
	//		player_->OnCollision();
	//		bullet->OnCollision();
	//	}*/
	//	CheckCollisionPair(player_, bullet);
	//}
	// #pragma endregion

	// #pragma region ジtamaと敵キャラの当たり判定
	//// 敵キャラの座標
	////posA = enemy_->GetWorldPosition();
	//// 敵キャラと自弾すべての当たり判定
	// for (PlayerBullet* bullet : playerBullets) {

	//	/*posB = bullet->GetWorldPosition();
	//	float distance = std::powf(posB.x - posA.x, 2.0f) + std::powf(posB.y - posA.y, 2.0f) +
	//	                 std::powf(posB.z - posA.z, 2.0f);

	//	if (distance <= std::powf(player_->GetRadius() + bullet->GetRadius(), 2.0f)) {
	//		enemy_->OnCollision();
	//		bullet->OnCollision();
	//	}*/
	//	CheckCollisionPair(enemy_, bullet);
	//}
	// #pragma endregion

	// #pragma region 自弾と敵弾の当たり判定
	//// 敵弾と自弾すべての当たり判定
	// for (PlayerBullet* pbullet : playerBullets) {
	//	for (EnemyBullet* ebullet : enemyBullets) {
	//		/*posA = pbullet->GetWorldPosition();
	//		posB = ebullet->GetWorldPosition();
	//		float distance = std::powf(posB.x - posA.x, 2.0f) + std::powf(posB.y - posA.y, 2.0f) +
	//		                 std::powf(posB.z - posA.z, 2.0f);

	//		if (distance <= std::powf(pbullet->GetRadius() + ebullet->GetRadius(), 2.0f)) {
	//			pbullet->OnCollision();
	//			ebullet->OnCollision();
	//		}*/
	//		CheckCollisionPair(pbullet, ebullet);
	//	}
	//}
	// #pragma endregion

	// コライダー
	// std::list<Collider*> colliders_;
	// コライダーをリストに登録
	colliders_.push_back(player_);
	for (Enemy* enemy : enemys_) {
		colliders_.push_back(enemy);
	}
	// 自弾すべてについて
	for (PlayerBullet* pbullet : playerBullets) {
		colliders_.push_back(pbullet);
	}
	for (EnemyBullet* ebullet : enemyBullets) {
		colliders_.push_back(ebullet);
	}

	// リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		Collider* colliderA = *itrA;
		// イテレーターBはイテレーターAの次の要素から回す（重複判定の回避）
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;

			// ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {

	// 衝突フィルタリング
	// 一致しなかったら当たり判定をとらない
	if (!(colliderA->GetcollisionAttribute() & colliderB->GetcollisionMask()) ||
	    !(colliderB->GetcollisionAttribute() & colliderA->GetcollisionMask())) {
		return;
	}

	// 判定対象AとBの座標
	Vector3 posA{}, posB{};

	posA = colliderA->GetWorldPosition();
	posB = colliderB->GetWorldPosition();

	float distance = std::pow(posB.x - posA.x, 2.0f) + std::powf(posB.y - posA.y, 2.0f) +
	                 std::pow(posB.z - posA.z, 2.0f);
	if (distance <= std::powf(colliderA->Getradius() + colliderB->Getradius(), 2.0f)) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}
