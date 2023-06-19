#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include<imgui.h>
class RailCamera 
{
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//ヴュープロジェクション
	ViewProjection viewProjection_;


public:
	

	void Initialize(const Vector3 worldpos, Vector3 radian);
	void Update();	
	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

};
