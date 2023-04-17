#pragma once
#include"Model.h"
#include"WorldTransform.h"

class Player {
private:
	//ワールド返還データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="model">モデル</param>
		/// <param name="textureHandle">テクスチャハンドル</param>
		void Initialize(Model* model,uint32_t textureHandle );

		void Update();

		void Draw(ViewProjection viewProjection);
};
