#include "Player.h"
#include "cassert"

void Player::Initialize(Model* model, uint32_t textureHandle, Vector3 playerpos) {
	// NULLポインタチェック
	assert(model);
	// 初期化各々
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	this->worldTransform_.Initialize();
	this->worldTransform_.translation_ = playerpos;
	input_ = Input::GetInstance();
	// 衝突判定を設定
	SetcollisionAttribute(kCollisionAttributePlayer);
	// 衝突対象を自分の属性以外に設定
	SetcollisionMask(~kCollisionAttributePlayer);
	// 3Dレティクルのワールドトランスフォーム初期化
	worldTransform3DReticle_.Initialize();
	// レティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("Reticle.png");
	// スプライト生成
	sprite2DReticle_ =
	    Sprite::Create(textureReticle, Vector2(0, 0), {255, 255, 255, 255}, Vector2(0.5, 0.5));
}

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}

	delete sprite2DReticle_;
}

void Player::Update(const ViewProjection& viewProjection) {
	// ですフラグの立った球の削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead() == true) {
			delete bullet;
			return true;
		}
		return false;
	});

	// キャラの移動ベクトル
	Vector3 move = {0, 0, 0};
	// kyらの移動の速さ
	const float kCharacterSpeed = 0.2f;

	CharaMove(move, kCharacterSpeed); // キャラクター移動処理
	CharaRotate();                    // キャラクター旋回処理
	worldTransform_.UpdateMatrix();
	//照準に向けて打つ
	Reticle(viewProjection);
	


	worldTransform_.translation_ += move;
	worldTransform_.UpdateMatrix();
	
	Attack(); // キャラクター攻撃処理
	// 行列をバッファに転送
	// worldTransform_.TransferMatrix();

	// 弾の更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	//worldTransform_.matWorld_ = MakeAffineMatrix(
	//    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	Inputfloat3[0] = worldTransform_.translation_.x;
	Inputfloat3[1] = worldTransform_.translation_.y;
	Inputfloat3[2] = worldTransform_.translation_.z;

	// キーボード入力による移動処理
	// 移動限界座標
	const float kMoveLimitX = 30;
	const float kMoveLimitY = 30;

	// 範囲を超えない処理
	worldTransform_.translation_.x =
	    std::clamp(worldTransform_.translation_.x, -kMoveLimitX, kMoveLimitX);
	worldTransform_.translation_.y =
	    std::clamp(worldTransform_.translation_.y, -kMoveLimitY, kMoveLimitY);

	// キャラクターの座標を画面表示する処理
	ImGui::Begin("Debug");
	// デバックテキスト表示
	ImGui::Text(
	    "Player %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	ImGui::Text(
	    "Player Position %f,%f,%f", 
		worldTransform_.matWorld_.m[3][0],
	    worldTransform_.matWorld_.m[3][1],
	    worldTransform_.matWorld_.m[3][2]);
	// ImGui::InputFloat3("Player", Inputfloat3);
	// ImGui::SliderFloat3("Player", Inputfloat3,0.0f,1.0f);
	ImGui::End();
}

void Player::CharaRotate() {
	const float kRotSpeed = 0.02f;
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

void Player::Draw(ViewProjection viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// 3Dレティクルを描画
	// Reticle_model_->Draw(worldTransform3DReticle_, viewProjection);

	// 弾描画
	for (PlayerBullet* bullet : bullets_) {

		bullet->Draw(viewProjection);
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		////弾があれば開放
		// if (bullet_) {
		//	delete bullet_;
		//	bullet_ = nullptr;
		// }
		//  弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		// 速度ベクトルヲ自機の向きに合わせて回転させる
		/* velocity = TransformNormal(velocity, worldTransform_.matWorld_);*/
		// 自機から照準オブジェクトへのベクトル
		Vector3 playermat = Vector3(
		    worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1],
		    worldTransform_.matWorld_.m[3][2]);
		velocity = worldTransform3DReticle_.translation_- playermat;
		velocity = Vector3::Normalize(velocity) * kBulletSpeed;
		/* worldTransform_.UpdateMatrix();*/
		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(model_, playermat, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	// worldTransform_.UpdateMatrix();
	// ワールド行列の平行移動成分を取得（ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return Vector3(worldPos);
}

void Player::OnCollision() {}

void Player::DrawUI() { sprite2DReticle_->Draw(); }

void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}

void Player::Reticle(const ViewProjection&viewProjection) 
{
	// 自機から３ｄレティクルへのオフセット(Z+向き)
	Vector3 offset = {0, 0, 1.0f};
	// 自機のワールド行列の回転を反映
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	offset = Transform(offset, worldTransform_.matWorld_);
	// ベクトルの長さを変える
	offset = Vector3::Normalize(offset) * kDistanceplayerTo3DReticle;
	// 3Dレティクルの座標を設定
	worldTransform3DReticle_.translation_ = offset;
	worldTransform3DReticle_.UpdateMatrix();
	// worldTransform3DReticle_.TransferMatrix();

	// 3Dレティクルのワールド座標から２Dレティクルのスクリーン座標を計算

	Vector3 positionReticle = worldTransform3DReticle_.translation_;
	// ビューポート行列
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	// ビューポート行列とプロジェクション行列、ビューポート行列を合成する
	Matrix4x4 matViewProjectionViewport =
	    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);
	// ワールドからスクリーン座標返還(ここで３ｄから２ｄへ）
	positionReticle = Transform(positionReticle, matViewProjectionViewport);
	// スプライトのレティクルに座標設定
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
}

void Player::CharaMove(Vector3& move, const float& kCharacterSpeed) {
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
}
