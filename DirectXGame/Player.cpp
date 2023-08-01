#include "Player.h"
#include <assert.h>
#include <cmath>
#include <numbers>
#include "imgui.h"
#include "Easing.h"

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

	worldTransformWeapon_.Initialize();

	worldTransformBase_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHead_.translation_ = {0.0f, 6.0f, 0.0f};
	worldTransformL_arm_.translation_ = {-2.0f, 5.5f, 0.0f};
	worldTransformR_arm_.translation_ = {2.0f, 5.5f, 0.0f};

	worldTransformBody_.parent_ = &GetWorldTransform();
	worldTransformHead_.parent_ = &GetWorldTransformBody();
	worldTransformL_arm_.parent_ = &GetWorldTransformBody();
	worldTransformR_arm_.parent_ = &GetWorldTransformBody();

	
}

void Player::Update() {

	if (behaviorRequest_) {

		behavior_ = behaviorRequest_.value();

		switch (behavior_) {
			case Behavior::kRoot:
		    default:
			    BehaviorRootInitialize();
				break;
			case Behavior::kAttack:
			    BehaviorAttackInitialize();
			    break;

		}

		behaviorRequest_ = std::nullopt;
	}

	BaseCharacter::Update();

	switch (behavior_) {
	    case Behavior::kRoot:
	    default:
		    BehaviorRootUpdate();
	    	break;
	    case Behavior::kAttack:
		    BehaviorAttackUpdate();
	    	break;
	}

	worldTransformBase_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	worldTransformWeapon_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);
	if (behavior_ == Behavior::kAttack) {
		 models_[4]->Draw(worldTransformWeapon_, viewProjection);
	}
	

}

void Player::InitializeFloatingGimmick() {

	floatingParameter_ = 0.0f;

}

void Player::UpdateFloatingGimmick() {
	
	//1フレームでのパラメータ加算値
	const float step = 2.0f * (float)std::numbers::pi / (float)cycle;

	floatingParameter_ += step;

	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * (float)std::numbers::pi);
	
	worldTransformBody_.translation_.y = std::sinf(floatingParameter_) * amplitude;

	amplitude = 0.5f;

	amplitude = 0.3f;

	worldTransformL_arm_.rotation_.y = std::sinf(floatingParameter_) * amplitude;
	worldTransformR_arm_.rotation_.y = std::sinf(floatingParameter_) * amplitude;

}

void Player::BehaviorRootInitialize() {

	amplitude = 0.5f;
	cycle = 60;

}

void Player::BehaviorRootUpdate() {
	XINPUT_STATE joyState;

	Vec3 move{};
	const float speed = 0.3f;
	Vec3 zeroVector{};

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		if (joyState.Gamepad.wButtons) {
			    behaviorRequest_ = Behavior::kAttack;
			    return;
		}

		move = {(float)joyState.Gamepad.sThumbLX, 0.0f, (float)joyState.Gamepad.sThumbLY};
		move = move / SHRT_MAX * speed;

		move = TransformNormal(move, MakeRotateYMatrix(viewProjection_->rotation_.y));

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

		if (input_->PushKey(DIK_SPACE)) {
			behaviorRequest_ = Behavior::kAttack;
			return;
		}

		move = TransformNormal(move, MakeRotateYMatrix(viewProjection_->rotation_.y));

		worldTransformBase_.translation_ += move;

		if (move != zeroVector) {
			rotate = move;
		}

		worldTransformBase_.rotation_.y = std::atan2(rotate.x, rotate.z);
	}

	UpdateFloatingGimmick();
}

void Player::BehaviorAttackInitialize() {

	num = 0.0f;
	worldTransformWeapon_ = worldTransformBase_;
	worldTransformWeapon_.translation_.y = 3.0f;
	count = 0;

}

void Player::BehaviorAttackUpdate() {

	num += 0.05f;
	float T = Easing::easeInSine(num);
	worldTransformWeapon_.rotation_.x =
	    Lerp(T, 0.0f, (float)std::numbers::pi / 2.0f);

	if (num >= 1.0f) {
		num = 1.0f;
		count++;
	}

	if (count == 15) {
		behaviorRequest_ = Behavior::kRoot;
	}
}