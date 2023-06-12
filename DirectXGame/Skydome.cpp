#include "Skydome.h"
#include<assert.h>

void Skydome::Initialize(Model* model)
{ 
	// NULLポインタチェック
	assert(model);

	worldTransform_.Initialize();
	worldTransform_.scale_ = {50.0f, 50.0f, 50.0f};

	worldTransform_.UpdateMatrix();
	model_ = model;
}

void Skydome::Update() {

}

void Skydome::Draw(const ViewProjection viewprojection) 
{
	// 3Dモデル描画
	model_->Draw(worldTransform_,viewprojection );
}


