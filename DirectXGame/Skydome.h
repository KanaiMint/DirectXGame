#pragma once
#include"WorldTransform.h"
#include"Model.h"

class Skydome 
{
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;

public:
	void Initialize(Model*model);
	void Update();
	void Draw(ViewProjection viewprojection);
	bool isClear;
};
