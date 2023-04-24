#include "Player.h"
#include "cassert"


void Player::Initialize(Model* model, uint32_t textureHandle) {
//NULLポインタチェック
	assert(model);
	//初期化各々
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	this->worldTransform_.Initialize();

	input_ = Input::GetInstance();

	
}

void Player::Update() {
//行列をバッファに転送
	worldTransform_.TransferMatrix();
	//キャラの移動ベクトル
	Vector3 move = {0, 0, 0};
	//kyらの移動の速さ
	const float kCharacterSpeed = 0.2f;

	CharaMove(move, kCharacterSpeed);
	worldTransform_.translation_ += move;
	worldTransform_.matWorld_= MakeAffineMatrix(
    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	Inputfloat3[0] = worldTransform_.translation_.x;
	Inputfloat3[1] = worldTransform_.translation_.y;
	Inputfloat3[2] = worldTransform_.translation_.z;

	//キーボード入力による移動処理
	//移動限界座標
	const float kMoveLimitX = 30;
	const float kMoveLimitY = 30;

	//範囲を超えない処理
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
	//ImGui::InputFloat3("Player", Inputfloat3);
	//ImGui::SliderFloat3("Player", Inputfloat3,0.0f,1.0f);
	ImGui::End();
}


void Player::Draw(ViewProjection viewProjection) {
//3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);


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
