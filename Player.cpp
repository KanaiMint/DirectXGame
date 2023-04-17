#include "Player.h"
#include "cassert"


void Player::Initialize(Model* model, uint32_t textureHandle) {
//NULLポインタチェック
	assert(model);
	//初期化各々
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	this->worldTransform_.Initialize();
}

void Player::Update() {
//行列をバッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection viewProjection) {
//3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

