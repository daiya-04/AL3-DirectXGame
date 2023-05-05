#include "Enemy.h"
#include<assert.h>
#include "Matrix44.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 2.0f, 40.0f};
	input_ = Input::GetInstance();
}

void Enemy::Update() {

	if (input_->TriggerKey(DIK_R)) {
		worldTransform_.translation_.z = 40.0f;
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, {0.0f, 0.0f, -0.3f});
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}