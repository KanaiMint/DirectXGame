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
	SetMask(Mask::player);
	// 3Dレティクルのワールドトランスフォーム初期化
	worldTransform3DReticle_.Initialize();
	// レティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("Reticle.png");
	// 上下判定用テクスチャ取得
	uint32_t textureHarf = TextureManager::Load("Harf.png");
	// スプライト生成
	sprite2DReticle_ = Sprite::Create(
	    textureReticle, Vector2(WinApp::kWindowWidth * 0.5f, WinApp::kWindowHeight * 0.5f),
	    {1, 1, 1, 1}, Vector2(0.5, 0.5));

	sprite2DWindowHarf = Sprite::Create(
	    textureHarf, Vector2(0,0)
	    );
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
	//ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;
	//ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}
	
	//ReticlePAD(viewProjection);
	// 照準に向けて打つ
	// Reticle(viewProjection);
	// マウスの照準に打つ
	// ReticleMouse(viewProjection);
	
	CharaMove(move, kCharacterSpeed); // キャラクター移動処理
	//CharaRotate();             
	
	worldTransform_.UpdateMatrix();

	
	ViewProjection hoge = viewProjection;
	
	//worldTransform_.UpdateMatrix();

	Attack(viewProjection); // キャラクター攻撃処理
	// 行列をバッファに転送
	// worldTransform_.TransferMatrix();

	// 弾の更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	// worldTransform_.matWorld_ = MakeAffineMatrix(
	//     worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

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
	    "Player Position %f,%f,%f", worldTransform_.matWorld_.m[3][0],
	    worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2]);
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

void Player::Attack(ViewProjection viewProjection) {
	
	AttackTime--;
	if (AttackTime < 0) {
		AttackTime = 0;
	}
	// 3Dのワールド座標から２Dのスクリーン座標を計算

	Vector3 positionWorld = worldTransform_.translation_;
	// ビューポート行列
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	// ビューポート行列とプロジェクション行列、ビューポート行列を合成する
	Matrix4x4 matViewProjectionViewport =
	    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);
	// ワールドからスクリーン座標返還(ここで３ｄから２ｄへ）
	positionWorld = Transform(positionWorld, matViewProjectionViewport);
	//画面の上半分か下半分かどうか
	if (positionWorld.y >= WinApp::kWindowHeight * 0.5f) {
		IsWindowUp = true;
		
	} else {
		IsWindowUp = false;	

	}
	//上半分にいたとき
	if (IsWindowUp == true) {
		if (input_->PushKey(DIK_SPACE) && ReflectCoolTime <= 0) {
			IsReflection = true;
		}
	} else if (IsWindowUp == false) {
	
	}
	//反射モードの処理
	if (IsReflection == true ) {
		worldTransform_.rotation_.y += ReflectRotateSpeed;
		ReflectTime++;
		if (ReflectTime > kMaxReflectTime) {
			ReflectCoolTime = kMaxReflectCoolTime;
			ReflectTime = 0;
			IsReflection = false;
		}
	} else if (IsReflection == false) {
		ReflectCoolTime--;

		worldTransform_.rotation_.y = 0;
	} // キャラクター旋回処理



	if (input_->IsPressMouse(0) && AttackTime == 0) {
		AttackTime = KAttackTimeParsent;
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
		velocity = worldTransform3DReticle_.translation_ - playermat;
		velocity = Vector3::Normalize(velocity) * kBulletSpeed;
		/* worldTransform_.UpdateMatrix();*/
		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(model_, playermat, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}


	XINPUT_STATE joyState;
	//ゲームパッドが未接続なら何もせず抜ける
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}
	//Rトリガーを押していたら

	if (joyState.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER) {
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
		velocity = worldTransform3DReticle_.translation_ - playermat;
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

void Player::DrawUI() {
	sprite2DReticle_->Draw();
	//sprite2DWindowHarf->Draw();
}

void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}

void Player::DrawHarf() 
{
	//上下判定用画像
	sprite2DWindowHarf->Draw();
}

void Player::Reticle(const ViewProjection& viewProjection) {
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

void Player::ReticleMouse(const ViewProjection& viewProjection) {
	// マウスカーソルのスクリーン座標からワールド座標を取得して３Dレティクルを配置

	POINT mousePosition;
	// マウス座標（スクリーン座標)を取得する
	GetCursorPos(&mousePosition);

	// クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);
	sprite2DReticle_->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));
	// ビューポート行列
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	// ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPN =
	    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);
	// 合成行列の逆行列を計算する
	Matrix4x4 matInverseVPV = Inverse(matVPN);

	// スクリーン座標
	Vector3 posNear = Vector3((float)mousePosition.x, (float)mousePosition.y, 0.0f);
	Vector3 posFar = Vector3((float)mousePosition.x, (float)mousePosition.y, 1.0f);
	// スクリーン座標からワールド座標へ
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	// マウスレイの方向
	Vector3 mouseDirection =  posFar-posNear;
	mouseDirection = Vector3::Normalize(mouseDirection);
	// カメラから照準オブジェクトの距離
	const float kDistanceTestObject = 100.0f;
	worldTransform3DReticle_.translation_ = posNear + (mouseDirection * kDistanceTestObject);

	worldTransform3DReticle_.UpdateMatrix();

	ImGui::Begin("Player");
	ImGui::Text(
	    "2DReticle:(%f,%f)", sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y);
	ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text(
	    "3DReticle:(%+.2f,%+.2f,%+.2f)", worldTransform3DReticle_.translation_.x,
	    worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::End();
}

void Player::ReticlePAD(const ViewProjection& viewProjection) 
{
	// スプライトの現在の座標を取得
	Vector2 spritePosition = sprite2DReticle_->GetPosition();
	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;
	// ジョイスティックの状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
		spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		// スプライトの座標変更を反映
		sprite2DReticle_->SetPosition(spritePosition);
	}
	
	sprite2DReticle_->SetPosition(Vector2((float)spritePosition.x, (float)spritePosition.y));
	// ビューポート行列
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	// ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPN =
	    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);
	// 合成行列の逆行列を計算する
	Matrix4x4 matInverseVPV = Inverse(matVPN);

	// スクリーン座標
	Vector3 posNear = Vector3((float)spritePosition.x, (float)spritePosition.y, 0.0f);
	Vector3 posFar = Vector3((float)spritePosition.x, (float)spritePosition.y, 1.0f);
	// スクリーン座標からワールド座標へ
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	// マウスレイの方向
	Vector3 mouseDirection = posFar - posNear;
	mouseDirection = Vector3::Normalize(mouseDirection);
	// カメラから照準オブジェクトの距離
	const float kDistanceTestObject = 100.0f;
	worldTransform3DReticle_.translation_ = posNear + (mouseDirection * kDistanceTestObject);

	worldTransform3DReticle_.UpdateMatrix();

	ImGui::Begin("Player");
	ImGui::Text(
	    "2DReticle:(%f,%f)", sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y);
	ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text(
	    "3DReticle:(%+.2f,%+.2f,%+.2f)", worldTransform3DReticle_.translation_.x,
	    worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::End();
	


}

bool Player::LockOnReticle(Vector3 EnemyPos, const ViewProjection& viewProjection,bool& flag) 
{	
	POINT mousePosition;
	// マウス座標（スクリーン座標)を取得する
	GetCursorPos(&mousePosition);
	// クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);
	// ビューポート行列
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	// ビューポート行列とプロジェクション行列、ビューポート行列を合成する
	Matrix4x4 matViewProjectionViewport =
	    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);
	// ワールドからスクリーン座標返還(ここで３ｄから２ｄへ）
	Vector3 Enemy2DPos = Transform(EnemyPos, matViewProjectionViewport);
	// ワールドからスクリーン座標返還(ここで３ｄから２ｄへ）
	Vector3 positionReticle =
	    Transform(worldTransform3DReticle_.translation_, matViewProjectionViewport);

	float direction = Vector2::Length(
	    Vector2(Enemy2DPos.x, Enemy2DPos.y),
	    Vector2((float)mousePosition.x, (float)mousePosition.y));
	// スプライトのレティクルに座標設定w
	if (direction < 50.0f) {
		flag = true;
		
	} 
	if (direction > 200) {
		flag = false;
	}
	if (flag == true) {
		worldTransform3DReticle_.translation_ = EnemyPos;
		worldTransform3DReticle_.UpdateMatrix();
		// ワールドからスクリーン座標返還(ここで３ｄから２ｄへ）
		positionReticle =
		    Transform(worldTransform3DReticle_.translation_, matViewProjectionViewport);
		// スプライトのレティクルに座標設定
		sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
		return true;
	}
	if (flag == false) {
		ReticleMouse(viewProjection);
		return false;
	}
		
	

	ImGui::Begin("Debug");
	// デバックテキスト表示
	ImGui::Text("Direction:%f", direction);
	ImGui::Text("PlayerReticle2D:%f %f", positionReticle.x, positionReticle.y);
	ImGui::Text("Enemy:%f %f", Enemy2DPos.x, Enemy2DPos.y);
	// ImGui::InputFloat3("Player", Inputfloat3);
	// ImGui::SliderFloat3("Player", Inputfloat3,0.0f,1.0f);
	ImGui::End();
	return false;
}

void Player::CharaMove(Vector3& move, const float& kCharacterSpeed) {
	if (input_->PushKey(DIK_LEFT)||input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP) || input_->PushKey(DIK_W)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN) || input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	}
	worldTransform_.translation_ += move;
}
