#include "FollowCamera.h"
#include "imgui.h"
#include <cmath>

void FollowCamera::Initialize() {

	viewProjection_.Initialize();
	input_ = Input::GetInstance();

}

void FollowCamera::Update() {

	XINPUT_STATE joyState;
	const float rotateSpeed = 0.01f;


	if (input_->PushKey(DIK_RIGHT)) {
		viewProjection_.rotation_.y -= rotateSpeed;
	}
	if (input_->PushKey(DIK_LEFT)) {
		viewProjection_.rotation_.y += rotateSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		viewProjection_.rotation_.x += rotateSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		if (viewProjection_.translation_.y > 0.1f) {
			viewProjection_.rotation_.x -= rotateSpeed;
		}
		
	}
	
	

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		viewProjection_.rotation_.y += ((float)joyState.Gamepad.sThumbRX / SHRT_MAX) * rotateSpeed;
		viewProjection_.rotation_.x += ((float)joyState.Gamepad.sThumbRY / SHRT_MAX) * rotateSpeed;
	}

	if (target_) {
	
		Vec3 offset = {0.0f, 5.0f, -30.0f};

		Matrix44 rotateMatrix = MakeRotateXMatrix(viewProjection_.rotation_.x) *
		                        MakeRotateYMatrix(viewProjection_.rotation_.y) *
		                        MakeRotateZMatrix(viewProjection_.rotation_.z);

		offset = TransformNormal(offset, rotateMatrix);

		viewProjection_.translation_ = target_->translation_ + offset;

		if (viewProjection_.translation_.y < 0.1f) {
			viewProjection_.translation_.y = 0.1f;
		}

	}

#ifdef _DEBUG
	ImGui::Begin("FollowCamera");
	ImGui::DragFloat3("Translation", &viewProjection_.translation_.x, 0.01f);
	ImGui::End();

#endif // _DEBUG

	
	
	viewProjection_.UpdateViewMatrix();

}