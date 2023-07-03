#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"EnemyBullet.h"
#include"Player.h"
#include"Collider.h"
//GameSceneの前方宣言
class GameScene;
class Enemy :public Collider{
private:
	//ゲームシーン
	GameScene* gameScene_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_=nullptr;
	int32_t textureHandle_=0u;
	//行動フェーズ
	enum class Phese {
		Approach,//接近
		Leave,//離脱
	};

	Phese phese_ = Phese::Approach;
	 Vector3 MoveSpeed = {0, 0, 0.01f};
	// 敵弾
	std::list<EnemyBullet*> bullets_;
	 const uint32_t kbullets_Interval = 60;
	uint32_t bullets_cooltime = kbullets_Interval;
	 Player* player_ = nullptr;
	bool isDead_ = false;

 public:
	 ~Enemy();
	void Initialize(Model* model,Vector3 pos);
	void Update();
	void Approach();
	void Draw(ViewProjection viewProjection);
	void Fire();
	void ApproachInitialize();
	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition()override;
	void OnCollision()override;
	const std::list<EnemyBullet*>& GetBullets() { return bullets_; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	inline bool IsDead() const { return isDead_; }
};
