#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include<list>
#include"Player.h"
#include"Collider.h"
class EnemyBullet :public Collider{
	private:

		WorldTransform worldTransform_;
	    Model* model_=nullptr;
	    uint32_t textureHandle_ = 0u;
	    static const int32_t killTimer = 60 * 5;
	    uint32_t deathTimer=killTimer;
	    Vector3 velocity_ = {};
	    bool isDead_ = false;
	    Player *player_;
	    float Radius = 1.0f;
	public:
	    ~EnemyBullet();

	   	void Initialize(Model* model, const Vector3& position,const Vector3& vel);
		void Update();
	    void Draw(ViewProjection& viewProjevtion);
	    inline bool IsDead() const { return isDead_; }
	    void SetPlayer(Player* player) { player_ = player; }
	    void OnCollision()override;
	    Vector3 GetWorldPosition()override;
	    float GetRadius() { return Radius; }



};
