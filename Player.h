#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "input.h"
#include "Matrix44.h"
#include "PlayerBullet.h"
#include <list>



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
	//弾
	std::list<PlayerBullet*> bullets_;

public:

	~Player();

	
	void Initialize(Model* model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);
	void Attack();

	Vector3 GetWorldPosition();
	
};
