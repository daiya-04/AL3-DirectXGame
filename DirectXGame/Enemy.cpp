#include "Enemy.h"
#include "Player.h"
#include<assert.h>
#include "Matrix44.h"
#include "ImGuiManager.h"

Enemy::~Enemy() {

	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void (Enemy::*Enemy::spFuncTable[])() = {
	&Enemy::ApproachUpdate, 
	&Enemy::LeaveUpdate
};

void Enemy::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {30.0f, 2.0f, 40.0f};
	input_ = Input::GetInstance();
	
	
	ApproachInitialize();
}

void Enemy::Update() {

	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	if (input_->TriggerKey(DIK_R)) {
		worldTransform_.translation_ = {30.0f, 2.0f, 40.0f};
		if (phase_ != Phase::Approach) {
			phase_ = Phase::Approach;
		}
		
	}

	/*switch (phase_) {
		case Phase::Approach:
	    default:
		    ApproachUpdate();
		    break;
		case Phase::Leave:
			LeaveUpdate();
		    break;
	}*/

	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	worldTransform_.UpdateMatrix();

#ifdef _DEBUG
	ImGui::Begin("Enemy");
	ImGui::Text(
	    "Position\n%.02f %.02f %.02f\n", worldTransform_.translation_.x,
	    worldTransform_.translation_.y, worldTransform_.translation_.z);
	if (phase_ == Phase::Approach) {
		    ImGui::Text("Phase : Approach\n");
	}
	if (phase_ == Phase::Leave) {
		    ImGui::Text("Phase : Leave\n");
	}
	ImGui::End();
#endif
}

void Enemy::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (EnemyBullet* bullet : bullets_) {
		    bullet->Draw(viewProjection);
	}
}


void Enemy::Fire() {
	
	assert(player_);

	const float kBulletSpeed = 1.0f;
	
	Vector3 worldPlayerPos = player_->GetWorldPosition();
	Vector3 worldEnemyPos = GetWorldPosition();
	Vector3 length = Sub(worldEnemyPos, worldPlayerPos);
	Vector3 velocity = Mul(kBulletSpeed,Normalize(length));

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);
}

void Enemy::OnCollision() {

}

void Enemy::ApproachInitialize() { 
	fireTimer = kFireInterval;
}

void Enemy::ApproachUpdate() {

	worldTransform_.translation_ = Add(worldTransform_.translation_, {0.0f, 0.0f, -0.01f});
	
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}

	fireTimer--;
	if (fireTimer == 0) {
	
		Fire();
		fireTimer = kFireInterval;
	}
}

void Enemy::LeaveUpdate() {

	worldTransform_.translation_ = Add(worldTransform_.translation_, {-0.07f, 0.08f, -0.2f});
}

Vector3 Enemy::GetWorldPosition() {

	Vector3 WorldPos;

	WorldPos.x = worldTransform_.matWorld_.m[3][0];
	WorldPos.y = worldTransform_.matWorld_.m[3][1];
	WorldPos.z = worldTransform_.matWorld_.m[3][2];

	return WorldPos;
}