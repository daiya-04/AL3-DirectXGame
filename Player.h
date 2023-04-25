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
	WorldTransform worldTransForm_;
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

	//初期化
	void Initialize(Model* model,uint32_t textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection viewProjection);
	//攻撃
	void Attack();
};
