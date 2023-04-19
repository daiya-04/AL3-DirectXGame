#include "Player.h"
#include <assert.h>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransForm_.Initialize();

}

void Player::Update() {
	worldTransForm_.TransferMatrix();


}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransForm_, viewProjection, textureHandle_);
}