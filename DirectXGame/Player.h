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
	//上下どっちにいるか用スプライト
	Sprite* sprite2DWindowHarf = nullptr;
	//ゲージスプライト
	Sprite* spriteGauge=nullptr;
	//ゲージスプライト
	Sprite* spriteGaugeBar=nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	Sprite* mouseSprite = nullptr;
	Sprite* moveSprite = nullptr;
	Sprite* SpaceSprite = nullptr;
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

	bool IsReflection = false;
	int ReflectTime = 0;
	int ReflectCoolTime = 120;
	const int kMaxReflectCoolTime = 120;
	
	float ReflectRotateSpeed = 0.5f;
	const int kMaxReflectTime = 60;
	int AttackTime = 0;
	const int KAttackTimeParsent = 20;//発射感覚
	bool IsWindowUp = false;
	float damageTime=0;
	const float kBulletSpeed = 3.0f;
	float Score = 0;
	uint32_t textureNum=0u;
	Sprite* manssprite = nullptr;
	Sprite* senssprite = nullptr;
	Sprite* tenssprite = nullptr;
	Sprite* minssprite = nullptr;
	int sensPlace=0;
	int tensPlace=0;
	int mansPlace=0;
	int minsPlace=0;
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
	    void DrawHarf();
	    void Attack(ViewProjection viewProjection);
	    Vector3 GetWorldPosition() override;
	    float GetRadius() { return Radius; }
	    bool GetIsReflection() { return IsReflection; }
	    void OnCollision(float damage) override;
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
	    Vector3 GetReticlePos() { return worldTransform3DReticle_.translation_; };

		bool LockOnReticle(Vector3 EnemyPos, const ViewProjection& viewProjection, bool& flag);
	    void GetsBullets(PlayerBullet* bullets);
	    Vector3 getplayermatpos() {
		    return  Vector3(
		               worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1],
		               worldTransform_.matWorld_.m[3][2]);
	    }
	    void GaugeDraw();
	    void ScoreUp();
	    void DrawScore();
};
