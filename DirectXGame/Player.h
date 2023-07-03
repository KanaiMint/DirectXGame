#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Input.h"
#include"Matrix4x4.h"
#include"ImGuiManager.h"
#include"PlayerBullet.h"
#include <list>
#include"Collider.h"
#include"Sprite.h"

class Player :public Collider {
private:
	//ワールド返還データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	Model* Reticle_model_ = nullptr;
	//2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;
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
	// 自機から3Dレティクルへの距離
	const float kDistanceplayerTo3DReticle = 20.0f;

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="model">モデル</param>
		/// <param name="textureHandle">テクスチャハンドル</param>
	    void Initialize(Model* model, uint32_t textureHandle, Vector3 playerpos);
	    ~Player();
	    void Update(const ViewProjection& viewProjection);

	    void CharaRotate();

	    void CharaMove(Vector3& move, const float& kCharacterSpeed);

		void Draw(ViewProjection viewProjection);
	    void DrawUI();
		void Attack();
	    Vector3 GetWorldPosition() override;
	    float GetRadius() { return Radius; }

		void OnCollision()override;
	    const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

		void SetParent(const WorldTransform* parent);
	    Matrix4x4 Getparent() { return worldTransform_.parent_->matWorld_; }
	    Matrix4x4 GetMatworld() { return worldTransform_.matWorld_; }
		//3Dレティクル用ワールドトランスフォーム
	    WorldTransform worldTransform3DReticle_;

		void Reticle(const ViewProjection& viewProjection);

	   void ReticlePAD(const ViewProjection& viewProjection);

		void ReticleMouse(const ViewProjection& viewProjection);

	    Vector3 MatWorldPlayerPos() 
		{
		   /* Matrix4x4 Mat= Multiply(worldTransform_.matWorld_, worldTransform_.parent_->matWorld_);
		    Vector3 tmp = Vector3(Mat.m[3][0], Mat.m[3][1], Mat.m[3][2]);*/
		    return {
		        worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1],
		        worldTransform_.matWorld_.m[3][2]};	
		}
		
};
