#pragma once
#include "Model.h"
#include "Vec3.h"
#include "Matrix44.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class PlayerBullet {
private:

	WorldTransform worldTransForm_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;


public:
	//初期化
	void Initialize(Model* model, const Vector3& position);
	//更新
	void Update();
	//描画
	void Draw(const ViewProjection& viewProjection);
};
