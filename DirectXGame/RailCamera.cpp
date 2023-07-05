#include "RailCamera.h"
#include "imgui.h"
#include "Vec3.h"
#include "Matrix44.h"

void RailCamera::Initialize(ViewProjection camera) {

	worldTransform_.translation_ = camera.translation_;
	worldTransform_.rotation_ = camera.rotation_;

	viewProjection_.farZ = camera.farZ;
	viewProjection_.Initialize();
}

void RailCamera::Update() {

	worldTransform_.translation_ += {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ += {0.0f, 0.001f, 0.0f};
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    {1.0f,1.0f,1.0f}, worldTransform_.rotation_, worldTransform_.translation_);

	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("Translation", &worldTransform_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("Rotation", &worldTransform_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();
	

}