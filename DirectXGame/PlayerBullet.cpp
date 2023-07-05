#include "PlayerBullet.h"
#include <assert.h>

void PlayerBullet::Initialize(Model* model, const Vec3& position, const Vec3& velocity) { 
	assert(model); 

	model_ = model;

	textureHandle_ = TextureManager::Load("Black.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	worldTransform_.UpdateMatrix();

	velocity_ = velocity;
}

void PlayerBullet::Update() {

	worldTransform_.translation_ += velocity_;

	worldTransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnCollision() {
	isDead_ = true;
}

Vec3 PlayerBullet::GetWorldPosition() {

	Vec3 WorldPos;

	WorldPos.x = worldTransform_.translation_.x;
	WorldPos.y = worldTransform_.translation_.y;
	WorldPos.z = worldTransform_.translation_.z;

	return WorldPos;
}