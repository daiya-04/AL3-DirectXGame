#include "Player.h"
#include <assert.h>
#include <cmath>

void Player::Initialize(Model* model) {

	assert(model);
	model_ = model;
	
	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.8f, 0.8f, 0.8f};
	worldTransform_.translation_ = {0.0f, 5.0f, 0.0f};
	rotate = {};

}

void Player::Update() {
	XINPUT_STATE joyState;

	Vec3 move{};
	const float speed = 0.3f;
	Vec3 zeroVector{};

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	
		

		move = {(float)joyState.Gamepad.sThumbLX, 0.0f, (float)joyState.Gamepad.sThumbLY};
		move = move / SHRT_MAX * speed;

		Matrix44 rotateMatrix = MakeRotateXMatrix(viewProjection_->rotation_.x) *
		                        MakeRotateYMatrix(viewProjection_->rotation_.y) *
		                        MakeRotateZMatrix(viewProjection_->rotation_.z);

		move = TransformNormal(move, rotateMatrix);

		worldTransform_.translation_ += move;

		if (move != zeroVector) {
			rotate = move;
		}

		worldTransform_.rotation_.y = std::atan2(rotate.x, rotate.z);

	} else {
		if (input_->PushKey(DIK_W)) {
			move.z += speed;
		}
		if (input_->PushKey(DIK_S)) {
			move.z -= speed;
		}
		if (input_->PushKey(DIK_D)) {
			move.x += speed;
		}
		if (input_->PushKey(DIK_A)) {
			move.x -= speed;
		}

		

		move = TransformNormal(move, MakeRotateYMatrix(viewProjection_->rotation_.y));

		worldTransform_.translation_ += move;

		if (move != zeroVector) {
			rotate = move;
		}

		worldTransform_.rotation_.y = std::atan2(rotate.x, rotate.z);

	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}

