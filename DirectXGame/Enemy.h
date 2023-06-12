#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"
#include <list>

class GameScene;
class Player;

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
	GameScene* gameScene_ = nullptr;
	
	uint32_t fireTimer = 0;
	Player* player_ = nullptr;

	Phase phase_ = Phase::Approach;

	static void (Enemy::*spFuncTable[])();

	bool isDead_ = false;

public:
	
	~Enemy();

	static const int kFireInterval = 60;

	void Initialize(Model* model, uint32_t textureHandle,Vector3 position);
	void Update();
	void Draw(ViewProjection viewProjection);
	void Fire();
	void OnCollision();

	void ApproachInitialize();
	void ApproachUpdate();
	void LeaveUpdate();

	Vector3 GetWorldPosition();
	bool isDead() const { return isDead_; }

	void SetPlayer(Player* player) { player_ = player; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
};


