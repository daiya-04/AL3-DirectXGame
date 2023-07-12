#include "Ground.h"
#include <assert.h>

void Ground::Initialize(Model* model) {

	assert(model);

	worldTransform_.Initialize();
	worldTransform_.scale_ = {100.0f, 100.0f, 100.0f};
	model_ = model;
	

}

void Ground::Update() {

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.UpdateMatrix();
}

void Ground::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}