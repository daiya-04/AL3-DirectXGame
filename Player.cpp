#include "Player.h"
#include "ImGuiManager.h"
#include <assert.h>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransForm_.Initialize();
	input_=Input::GetInstance();
}

void Player::Update() {
	
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;


	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	worldTransForm_.translation_ = Add(worldTransForm_.translation_, move);

	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	worldTransForm_.translation_.x = max(worldTransForm_.translation_.x, -kMoveLimitX);
	worldTransForm_.translation_.x = min(worldTransForm_.translation_.x, +kMoveLimitX);
	worldTransForm_.translation_.y = max(worldTransForm_.translation_.y, -kMoveLimitY);
	worldTransForm_.translation_.y = min(worldTransForm_.translation_.y, +kMoveLimitY);

	worldTransForm_.matWorld_ = MakeAffineMatrix(worldTransForm_.scale_, worldTransForm_.rotation_, worldTransForm_.translation_);

	worldTransForm_.TransferMatrix();

	ImGui::Begin("debug");
	ImGui::Text("%.02f %.02f %.02f", worldTransForm_.translation_.x, worldTransForm_.translation_.y,worldTransForm_.translation_.z);
	ImGui::End();


}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransForm_, viewProjection, textureHandle_);
}