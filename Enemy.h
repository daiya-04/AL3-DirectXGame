#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"


class Enemy {
private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;

public:

	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);
};
