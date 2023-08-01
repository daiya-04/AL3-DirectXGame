#include "Enemy.h"
#include <cmath>
#include <numbers>
#include "imgui.h"

void Enemy::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);
	models_ = models;

	rotate = {};

	worldTransformBase_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();

	worldTransformBase_.scale_ = {0.8f, 0.8f, 0.8f};
	worldTransformBase_.translation_ = {0.0f, 0.0f, 100.0f};
	worldTransformBody_.translation_ = {};
	worldTransformHead_.translation_ = {};

	worldTransformBody_.parent_ = &GetWorldTransform();
	worldTransformHead_.parent_ = &GetWorldTransformBody();

}

void Enemy::Update() {

	Vec3 move{};
	const float speed = 0.3f;
	const float angleSpeed = 0.01f;
	Vec3 zeroVector{};

	move.z += speed;
	angle += angleSpeed;
	angle = std::fmod(angle, 2.0f * (float)std::numbers::pi);
	
	move = TransformNormal( move , MakeRotateYMatrix(angle));

	worldTransformBase_.translation_ += move;

	if (move != zeroVector) {
		rotate = move;
	}

	worldTransformBase_.rotation_.y = std::atan2(rotate.x, rotate.z);


	worldTransformBase_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);

}