#pragma once
#include "Model.h"
#include "Vec3.h"
#include "Matrix44.h"
#include "WorldTransform.h"
#include "ViewProjection.h"


class EnemyBullet {
private:

	WorldTransform worldtransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;

	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

public:

	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	bool isDead() const { return isDead_; }


};
