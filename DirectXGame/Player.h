#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "input.h"
#include "Matrix44.h"
#include <list>
#include "Sprite.h"


class GameScene;
class Player {
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//キーボードの入力
	Input* input_ = nullptr;

	GameScene* gameScene_ = nullptr;

	//3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3Dreticle_;

	//2Dレティクル用スプライト
	Sprite* sprite2DReticle = nullptr;
	

public:

	~Player();

	
	void Initialize(Model* model,uint32_t textureHandle);
	void Update(ViewProjection viewProjection);
	void Draw(ViewProjection viewProjection);
	void DrawUI();
	void Attack();
	void OnCollision();

	Vec3 GetWorldPosition();

	void SetParent(const WorldTransform* parent);
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
};
