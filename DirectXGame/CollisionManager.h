#pragma once
#include "Collider.h"
#include "Enemy.h"
#include "Player.h"
#include <list>
class CollisionManager {
private:
	// コライダーリスト
	std::list<Collider*> colliders_;
	Player* player_;
	Enemy* enemy_;

public:
	void Initialize(Player* player);
	void Update(Player* player, std::list<Enemy*>& enemy, std::list<EnemyBullet*>& enemyBullets_);
	void CheckAllCollision(std::list<Enemy*>& enemys, std::list<EnemyBullet*>& enemyBullets_);
//	void Update(Player* player, Enemy* enemy, std::list<EnemyBullet*>& enemyBullets_);
	// void Update(Player* player, Enemy* enemy);
	//void CheckAllCollision(std::list<EnemyBullet*>& enemyBullets_);
	// void CheckAllCollision();
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
};
