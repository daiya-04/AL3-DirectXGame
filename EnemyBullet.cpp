#include "EnemyBullet.h"
#include<assert.h>

void EnemyBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {
	
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("Red.png");

	worldtransform_.Initialize();
	worldtransform_.translation_ = position;

	velocity_ = velocity;
}

void EnemyBullet::Update() {

	worldtransform_.translation_ = Sub(worldtransform_.translation_,velocity_);

	worldtransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldtransform_, viewProjection, textureHandle_);
}

