#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include"DebugCamera.h"
#include"CollisionManager.h"
#include"Skydome.h"
#include"RailCamera.h"
#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;
	// 3dモデルデータ
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// ジキャラ
	Player* player_ = nullptr;
	Model* modelPlayer_ = nullptr;
	// 敵キャラ
	// Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemys_;
	Model* modelEnemy_ = nullptr;

	// 敵弾リスト
	std::list<EnemyBullet*> enemyBullets_;
	// 天球
	Skydome* skydome_ = nullptr;
	// 天球3Dモデル
	Model* modelSkydome_ = nullptr;
	// コライダーマネージャー
	CollisionManager* collisionmanager_;
	// レールカメラ
	RailCamera* railCamera_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	///
	// デバックカメラ有効
	bool isDebugCameraActive_ = false;
	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	void CheckAllCollision();
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	Sprite* TitleSprite = nullptr;
	Sprite* ClearSprite = nullptr;
	

	// 敵発生コマンド
	std::stringstream enemyPopCommands;
	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();
	/// <summary>
	/// 敵の発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	void EnemyPop(Vector3 v, Model* model);

	bool isWait;
	int32_t WaitTime;

	enum Scene {
		Title,
		Stage
	};
	Scene scene = Title;

};