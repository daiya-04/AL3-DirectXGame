#include "Skydome.h"
#include <assert.h>

void Skydome::Initialize(Model* model) {

	assert(model);
	worldTransform_.Initialize();
	//viewProjection_.Initialize();
	model_ = model;

}

void Skydome::Update() {

	worldTransform_.translation_ = {0, 0, 0};

}

void Skydome::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}