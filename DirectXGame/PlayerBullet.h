#pragma once
#include "Model.h"
#include "Vec3.h"
#include "Matrix44.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class PlayerBullet {
private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vec3 velocity_;

	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

public:
	//初期化
	void Initialize(Model* model, const Vec3& position, const Vec3& velocity);
	//更新
	void Update();
	//描画
	void Draw(const ViewProjection& viewProjection);

	void OnCollision();

	bool isDead() const { return isDead_; }
	Vec3 GetWorldPosition();
	
};
