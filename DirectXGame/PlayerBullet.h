#pragma once
#include"Model.h"
#include"Collider.h"
#include"WorldTransform.h"
/// <summary>
/// ジキャラの弾
/// </summary>
class PlayerBullet :public Collider{
	private:
	WorldTransform worldTransform_;
	Model* model_=nullptr;
	uint32_t textureHandle_=0u;
	//速度
	Vector3 velocity_ = {};
	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//ですタイマー
	int32_t deathTimer_ = kLifeTime;
	//ですフラグ
	bool isDead_ = false;
	float Radius = 1.0f;
	bool isHarfUpWindow = false;
	

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	void Initialize(
	    Model* model, const Vector3& position, const Vector3& velocity, bool isharfwindow);
	void Initialize(
	    Model* model, const Vector3& position, const Vector3& velocity, bool isharfwindow,
	    float radius, Vector3 scale);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);
	inline bool IsDead() const { return isDead_; }
	void OnCollision(float damage) override;
	void OnCollision2(float damage) override;
	Vector3 GetWorldPosition() override {
		Vector3 worldPos;
		// ワールド行列の平行移動成分を取得（ワールド座標)
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];
		return worldPos;
	}
	float GetRadius() { return Radius; }
};
