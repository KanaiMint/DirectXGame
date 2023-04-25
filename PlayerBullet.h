#pragma once
#include"Model.h"
#include"WorldTransform.h"
/// <summary>
/// ジキャラの弾
/// </summary>
class PlayerBullet {
	private:
	WorldTransform worldTransform_;
	Model* model_=nullptr;
	uint32_t textureHandle_=0u;
	//速度
	Vector3 velocity_;
	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//ですタイマー
	int32_t deathTimer_ = kLifeTime;
	//ですフラグ
	bool isDead_ = false;
	

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
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
	

};
