#pragma once
#include "Model.h"
#include "Vec3.h"
#include "Matrix44.h"
#include "WorldTransform.h"
#include "ViewProjection.h"


class EnemyBullet {
private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vec3 velocity_;

	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

public:

	void Initialize(Model* model,const Vec3& position,const Vec3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void OnCollision();

	bool isDead() const { return isDead_; }
	Vec3 GetWorldPosition();


};
