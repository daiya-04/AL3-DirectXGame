#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"
#include "EnemyBullet.h"
#include <list>


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
	std::list<EnemyBullet*> bullets_;
	uint32_t fireTimer = 0;

	Phase phase_ = Phase::Approach;

	static void (Enemy::*spFuncTable[])();

public:
	
	~Enemy();

	static const int kFireInterval = 60;

	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);
	void Fire();

	void ApproachInitialize();
	void ApproachUpdate();
	void LeaveUpdate();
};
