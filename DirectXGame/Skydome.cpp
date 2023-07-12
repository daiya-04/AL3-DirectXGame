#include "Skydome.h"
#include <assert.h>

void Skydome::Initialize(Model* model) {

	assert(model);
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	model_ = model;
}

void Skydome::Update() {

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.UpdateMatrix();
}

void Skydome::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}