#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"
#include <list>

class GameScene;
class Player;
class Enemy;

class BaseEnemyState {
protected:
	Enemy* enemy_ = nullptr;
public:
	virtual ~BaseEnemyState();
	virtual void Update() = 0;
};

class EnemyStateApproach : public BaseEnemyState {
public:
	~EnemyStateApproach();
	void Initialize();
	void Update() override;
};

class EnemyStateLeave : public BaseEnemyState {
public:
	~EnemyStateLeave();
	void Update() override;
};

class Enemy {
private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	GameScene* gameScene_ = nullptr;
	
	uint32_t fireTimer = 0;
	Player* player_ = nullptr;

	BaseEnemyState* state_ = nullptr;

	bool isDead_ = false;

public:
	
	~Enemy();

	static const int kFireInterval = 60;

	void Initialize(Model* model, uint32_t textureHandle,Vec3 position);
	void Update();
	void Draw(ViewProjection viewProjection);
	void Fire();
	void OnCollision();
	void ChangeState(BaseEnemyState* newState);
	void EnemyMove(const Vec3& move);

	Vec3 GetLocalPosition();
	Vec3 GetWorldPosition();
	bool isDead() const { return isDead_; }

	void SetPlayer(Player* player) { player_ = player; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
};


