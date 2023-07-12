#include "Player.h"
#include <assert.h>

void Player::Initialize(Model* model) {

	assert(model);
	model_ = model;
	

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.8f, 0.8f, 0.8f};
	worldTransform_.translation_ = {0.0f, 5.0f, 0.0f};

}

void Player::Update() {

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}