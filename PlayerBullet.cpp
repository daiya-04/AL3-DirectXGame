#include "PlayerBullet.h"
#include <assert.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position) { 
	assert(model); 

	model_ = model;

	textureHandle_ = TextureManager::Load("Black.png");

	worldTransForm_.Initialize();
	worldTransForm_.translation_ = position;

	worldTransForm_.UpdateMatrix();
}

void PlayerBullet::Update() {

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransForm_, viewProjection, textureHandle_);
}