#include "Enemy.h"
#include<assert.h>
#include "Matrix44.h"
#include "ImGuiManager.h"

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
		worldTransform_.translation_ = {0.0f, 2.0f, 40.0f};
		if (phase_ != Phase::Approach) {
			phase_ = Phase::Approach;
		}
		
	}

	switch (phase_) {
		case Phase::Approach:
	    default:
		    ApproachUpdate();
		    break;
		case Phase::Leave:
			LeaveUpdate();
		    break;
	}

	worldTransform_.UpdateMatrix();

#ifdef _DEBUG
	ImGui::Begin("Enemy");
	ImGui::Text(
	    "Position\n%.02f %.02f %.02f\n", worldTransform_.translation_.x,
	    worldTransform_.translation_.y, worldTransform_.translation_.z);
	if (phase_ == Phase::Approach) {
		    ImGui::Text("Phase : Approach\n");
	}
	if (phase_ == Phase::Leave) {
		    ImGui::Text("Phase : Leave\n");
	}
	ImGui::End();
#endif
}

void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::ApproachUpdate() {

	worldTransform_.translation_ = Add(worldTransform_.translation_, {0.0f, 0.0f, -0.3f});

	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::LeaveUpdate() {

	worldTransform_.translation_ = Add(worldTransform_.translation_, {-0.07f, 0.08f, -0.2f});
}