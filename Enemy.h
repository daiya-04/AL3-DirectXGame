#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"


class Enemy {
private:

	enum class Phase {
		Approach,
		Leave,
	};

	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;

	Phase phase_ = Phase::Approach;

	static void (Enemy::*spFuncTable[])();

public:

	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);

	void ApproachUpdate();
	void LeaveUpdate();
};
