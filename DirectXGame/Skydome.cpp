#include "Skydome.h"
#include <assert.h>
#include <imgui.h>
void Skydome::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	worldTransform_.Initialize();
	worldTransform_.scale_ = {300.0f, 300.0f, 300.0f};

	worldTransform_.UpdateMatrix();
	isClear = false;
	model_ = model;
}

void Skydome::Update() {
	//ImGui::Begin("dome");
	//// デバックテキスト表示
	//ImGui::Text(
	//    "domepos %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	//    worldTransform_.translation_.z);
	//ImGui::Text(
	//    "domerotate %f,%f,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	//    worldTransform_.rotation_.z);
	//ImGui::DragFloat3("domerotate", &worldTransform_.rotation_.x, 10.1f);
	//ImGui::End();
	if (worldTransform_.translation_.z > -5500) {
		worldTransform_.translation_ -= Vector3(0.0f, 0.0f, 2.0f);
		worldTransform_.UpdateMatrix();
	}
	else {
		isClear = true;
	}
}

void Skydome::Draw(const ViewProjection viewprojection) {
	// 3Dモデル描画
	model_->Draw(worldTransform_, viewprojection);
}
