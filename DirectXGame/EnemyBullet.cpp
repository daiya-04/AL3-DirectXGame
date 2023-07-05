#include "EnemyBullet.h"
#include<assert.h>

void EnemyBullet::Initialize(Model* model, const Vec3& position,const Vec3& velocity) {
	
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("Red.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	velocity_ = velocity;
}

void EnemyBullet::Update() {

	worldTransform_.translation_ -= velocity_;

	worldTransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyBullet::OnCollision() { 
	isDead_ = true;
}

Vec3 EnemyBullet::GetWorldPosition() {

	Vec3 WorldPos;

	WorldPos.x = worldTransform_.translation_.x;
	WorldPos.y = worldTransform_.translation_.y;
	WorldPos.z = worldTransform_.translation_.z;

	return WorldPos;
}