#include "EnemyBullet.h"
#include<assert.h>

void EnemyBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {
	
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("Red.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	velocity_ = velocity;
}

void EnemyBullet::Update() {

	worldTransform_.translation_ = Sub(worldTransform_.translation_,velocity_);

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

Vector3 EnemyBullet::GetWorldPosition() {

	Vector3 WorldPos;

	WorldPos.x = worldTransform_.translation_.x;
	WorldPos.y = worldTransform_.translation_.y;
	WorldPos.z = worldTransform_.translation_.z;

	return WorldPos;
}