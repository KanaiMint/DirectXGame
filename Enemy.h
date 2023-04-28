#pragma once
#include"Model.h"
#include"WorldTransform.h"
class Enemy {
private:
	WorldTransform worldTransform_;
	Model* model_=nullptr;
	int32_t textureHandle_=0u;
	//行動フェーズ
	enum class Phese {
		Approach,//接近
		Leave,//離脱
	};

	Phese phese_ = Phese::Approach;
	 Vector3 MoveSpeed = {0, 0, 0.7f};
	
public:
	void Initialize(Model* model);
	void Update();
	void Approach();
	void Draw(ViewProjection viewProjection);
};
