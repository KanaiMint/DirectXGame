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


public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	

};
