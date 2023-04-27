#include "PlayerBullet.h"
#include <assert.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) { 
	assert(model); 

	model_ = model;

	textureHandle_ = TextureManager::Load("Black.png");

	worldTransForm_.Initialize();
	worldTransForm_.translation_ = position;

	worldTransForm_.UpdateMatrix();

	velocity_ = velocity;
}

void PlayerBullet::Update() {

	worldTransForm_.translation_ = Add(worldTransForm_.translation_, velocity_);

	worldTransForm_.UpdateMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransForm_, viewProjection, textureHandle_);
}