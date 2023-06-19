#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Input.h"
#include"Matrix4x4.h"
#include"ImGuiManager.h"
#include"PlayerBullet.h"
#include <list>
#include"Collider.h"

class Player :public Collider {
private:
	//ワールド返還データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//キーボード入力
	Input* input_ = nullptr;

	//スケーリング行列の作成
	Matrix4x4 AffineMatrix = {};
	float Inputfloat3[3] = {};

	//弾
	std::list<PlayerBullet*> bullets_;
	float Radius=5.0f;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="model">モデル</param>
		/// <param name="textureHandle">テクスチャハンドル</param>
	    void Initialize(Model* model, uint32_t textureHandle, Vector3 playerpos);
	    ~Player();
		void Update();

	    void CharaRotate();

	    void CharaMove(Vector3& move, const float& kCharacterSpeed);

		void Draw(ViewProjection viewProjection);

		void Attack();
	    Vector3 GetWorldPosition() override;
	    float GetRadius() { return Radius; }

		void OnCollision()override;
	    const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

		void SetParent(const WorldTransform* parent);
};
