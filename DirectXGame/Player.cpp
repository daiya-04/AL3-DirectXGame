#include "Player.h"
#include <assert.h>
#include <cmath>
#include <numbers>
#include "imgui.h"

void Player::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);
	models_ = models;



	/*modelBody_ = modelBody;
	modelHead_ = modelHead;
	modelL_arm_ = modelL_arm;
	modelR_arm_ = modelR_arm;*/
	
	input_ = Input::GetInstance();
	InitializeFloatingGimmick();

	rotate = {};

	worldTransformBase_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	worldTransformBase_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHead_.translation_ = {0.0f, 6.0f, 0.0f};
	worldTransformL_arm_.translation_ = {-2.0f, 5.5f, 0.0f};
	worldTransformR_arm_.translation_ = {2.0f, 5.5f, 0.0f};

	worldTransformBody_.parent_ = &GetWorldTransform();
	worldTransformHead_.parent_ = &GetWorldTransformBody();
	worldTransformL_arm_.parent_ = &GetWorldTransformBody();
	worldTransformR_arm_.parent_ = &GetWorldTransformBody();

	worldTransformBase_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Player::Update() {

	BaseCharacter::Update();
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

		worldTransformBase_.translation_ += move;

		if (move != zeroVector) {
			rotate = move;
		}

		worldTransformBase_.rotation_.y = std::atan2(rotate.x, rotate.z);

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

		worldTransformBase_.translation_ += move;

		if (move != zeroVector) {
			rotate = move;
		}

		worldTransformBase_.rotation_.y = std::atan2(rotate.x, rotate.z);

	}

	UpdateFloatingGimmick();


	worldTransformBase_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);

}

void Player::InitializeFloatingGimmick() {

	floatingParameter_ = 0.0f;

}

void Player::UpdateFloatingGimmick() {
	//浮遊移動のサイクル<frame>
	int cycle = 60;
	//1フレームでのパラメータ加算値
	const float step = 2.0f * (float)std::numbers::pi / cycle;

	floatingParameter_ += step;

	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * (float)std::numbers::pi);

	//浮遊の振幅
	float amplitude = 0.5f;
	
	worldTransformBody_.translation_.y = std::sinf(floatingParameter_) * amplitude;

	amplitude = 0.3f;

	worldTransformL_arm_.rotation_.y = std::sinf(floatingParameter_) * amplitude;
	worldTransformR_arm_.rotation_.y = std::sinf(floatingParameter_) * amplitude;

}