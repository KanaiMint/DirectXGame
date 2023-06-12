#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_; 
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete collisionmanager_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	//モデルの作成
	model_=Model::Create();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//ジキャラ作成
	player_ = new Player();
	//ジキャラの初期化
	player_->Initialize(model_,textureHandle_);
	//エネミー作成
	enemy_ = new Enemy();
	//エネミーの初期ka
	enemy_->Initialize(model_);
	//敵キャラにジキャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	//コリジョンマネージャー
	collisionmanager_ = new CollisionManager();
	//コリジョンマネージャーの初期化
	collisionmanager_->Initialize(player_, enemy_);
	//デバックカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("sora", true);
	//天球初期化
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);
}

void GameScene::Update() {
	//天球更新
	skydome_->Update();

//ジキャラの更新
	player_->Update();
	//敵の更新
	enemy_->Update();

	//当たり判定
	//CheckAllCollision();
	collisionmanager_->Update(player_,enemy_);

	//デバックカメラの更新
	debugCamera_->Update();
	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		//ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_C)) {
		if (isDebugCameraActive_ == false) {
			isDebugCameraActive_ = true;		
		} else {

			isDebugCameraActive_ = false;
		}
	}
	#endif
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//天球描画
	skydome_->Draw(viewProjection_);
	//自キャラの描画
	player_->Draw(viewProjection_);
	//敵キャラの描画
	enemy_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollision() 
{
	//判定対象AとBの座標
//	Vector3 posA, posB;
	//自弾リストの取得
	const std::list<PlayerBullet*> playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*> enemyBullets = enemy_->GetBullets();

	//#pragma region ジキャラと敵弾の当たり判定
	//////ジキャラの座標
	////posA = player_->GetWorldPosition();
	////ジキャラと敵弾すべての当たり判定
	//for (EnemyBullet* bullet : enemyBullets) {
	//
	//	/*posB = bullet->GetWorldPosition();
	//	float distance =
	//	    std::powf(posB.x - posA.x,2.0f) + std::powf(posB.y - posA.y,2.0f) + std::powf(posB.z - posA.z,2.0f);

	//	if (distance <= std::powf(player_->GetRadius() + bullet->GetRadius(),2.0f)) {
	//		player_->OnCollision();
	//		bullet->OnCollision();
	//	}*/
	//	CheckCollisionPair(player_, bullet);
	//}
	//#pragma endregion

	//#pragma region ジtamaと敵キャラの当たり判定
	//// 敵キャラの座標
	////posA = enemy_->GetWorldPosition();
	//// 敵キャラと自弾すべての当たり判定
	//for (PlayerBullet* bullet : playerBullets) {

	//	/*posB = bullet->GetWorldPosition();
	//	float distance = std::powf(posB.x - posA.x, 2.0f) + std::powf(posB.y - posA.y, 2.0f) +
	//	                 std::powf(posB.z - posA.z, 2.0f);

	//	if (distance <= std::powf(player_->GetRadius() + bullet->GetRadius(), 2.0f)) {
	//		enemy_->OnCollision();
	//		bullet->OnCollision();
	//	}*/
	//	CheckCollisionPair(enemy_, bullet);
	//}
	//#pragma endregion

	//#pragma region 自弾と敵弾の当たり判定
	//// 敵弾と自弾すべての当たり判定
	//for (PlayerBullet* pbullet : playerBullets) {
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
	//#pragma endregion

	//コライダー
	std::list<Collider*> colliders_;
	//コライダーをリストに登録
	colliders_.push_back(player_);
	colliders_.push_back(enemy_);
	//自弾すべてについて
	for (PlayerBullet* pbullet : playerBullets) {
		colliders_.push_back(pbullet);
	}
	for (EnemyBullet* ebullet : enemyBullets) {
		colliders_.push_back(ebullet);
	}

	//リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		Collider* colliderA = *itrA;
		//イテレーターBはイテレーターAの次の要素から回す（重複判定の回避）
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;

			//ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}

	}
}

void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {


	//衝突フィルタリング
	//一致しなかったら当たり判定をとらない
	if (!(colliderA->GetcollisionAttribute() & colliderB->GetcollisionMask())||
	    !(colliderB->GetcollisionAttribute() & colliderA->GetcollisionMask())) {
		return;
	}

	// 判定対象AとBの座標
	Vector3 posA{}, posB{};

	posA=colliderA->GetWorldPosition();
	posB=colliderB->GetWorldPosition();
	float distance = std::pow(posB.x - posA.x, 2.0f) + std::powf(posB.y - posA.y, 2.0f) +
	                 std::pow(posB.z - posA.z, 2.0f);
	if (distance <= std::powf(colliderA->Getradius() + colliderB->Getradius(), 2.0f)) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}
