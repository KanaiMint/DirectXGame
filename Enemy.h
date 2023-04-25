#pragma once
#include"Model.h"
#include"WorldTransform.h"
class Enemy {
private:
	WorldTransform worldTransform_;
	Model* model_=nullptr;
	int32_t textureHandle_=0u;

public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);
};
