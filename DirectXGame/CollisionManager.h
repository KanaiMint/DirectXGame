#pragma once
#include <list>
#include"Collider.h"
#include"Player.h"
#include"Enemy.h"
class CollisionManager {
private:
	//コライダーリスト
	std::list<Collider*> colliders_;
	Player* player_;
	Enemy* enemy_;

public:

	void Initialize(Player* player, Enemy* enemy);
	void Update(Player* player, Enemy* enemy);
	void CheckAllCollision();
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

};
