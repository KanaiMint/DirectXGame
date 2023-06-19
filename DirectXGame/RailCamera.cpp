#include "RailCamera.h"

void RailCamera::Initialize(const Vector3 worldpos, Vector3 radian) {
	//ワールドトランスフォームの初期設定
	//worldTransform_.Initialize();
	worldTransform_.rotation_ = radian;
	worldTransform_.translation_ = worldpos;
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void RailCamera::Update() 
{ 
	worldTransform_.translation_ += {0.0f,0.0f,-0.01f};
	worldTransform_.rotation_ += {0.0f,0.01f,0.0f};
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_,
		worldTransform_.rotation_,
		worldTransform_.translation_);
	//worldTransform_.UpdateMatrix();

	//カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	//カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	// デバックテキスト表示
	ImGui::Text(
	    "CameraTransform %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	ImGui::Text(
	    "CameraRotate %f,%f,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	    worldTransform_.rotation_.z);
	ImGui::End();

}
