#include "Enemy.h"
#include "Player.h"
#include<assert.h>
#include "Matrix44.h"
#include "ImGuiManager.h"
#include "GameScene.h"



Enemy::~Enemy() { 
	delete state_;
}

void Enemy::Initialize(Model* model, uint32_t textureHandle, Vec3 position) { 
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	input_ = Input::GetInstance();
	state_ = new EnemyStateApproach();
	
	
}

void Enemy::Update() {

	state_->Update();

	worldTransform_.UpdateMatrix();

#ifdef _DEBUG
	ImGui::Begin("Enemy");
	ImGui::Text(
	    "Position\n%.02f %.02f %.02f\n", worldTransform_.translation_.x,
	    worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::End();
#endif
}

void Enemy::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


void Enemy::Fire() {
	
	assert(player_);

	const float kBulletSpeed = 1.0f;
	
	Vec3 worldPlayerPos = player_->GetWorldPosition();
	Vec3 worldEnemyPos = GetWorldPosition();
	Vec3 length = worldEnemyPos - worldPlayerPos;
	Vec3 velocity = kBulletSpeed * length.Normalize();

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	gameScene_->AddEnemyBullet(newBullet);
}

void Enemy::OnCollision() { isDead_ = true; }

void Enemy::ChangeState(BaseEnemyState* newState) {
	delete state_; 
	state_ = newState;
}

void Enemy::EnemyMove(const Vec3& move) {
	worldTransform_.translation_ += move;
}



Vec3 Enemy::GetLocalPosition() {

	Vec3 localPos;

	localPos.x = worldTransform_.translation_.x;
	localPos.y = worldTransform_.translation_.y;
	localPos.z = worldTransform_.translation_.z;

	return localPos;
}

Vec3 Enemy::GetWorldPosition() {

	Vec3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

BaseEnemyState::~BaseEnemyState() { delete enemy_;}

EnemyStateApproach::~EnemyStateApproach() { delete enemy_; }

void EnemyStateApproach::Initialize() {
	//fireTimer = kFireInterval;
}

void EnemyStateApproach::Update() {
	
	enemy_->EnemyMove({0.0f, 0.0f, -0.1f});

	if (enemy_->GetLocalPosition().z < 0.0f) {
		    enemy_->ChangeState(new EnemyStateLeave());
	}

	/*fireTimer--;
	if (fireTimer == 0) {

		    Fire();
		    fireTimer = kFireInterval;
	}*/
}

EnemyStateLeave::~EnemyStateLeave() { delete enemy_; }

void EnemyStateLeave::Update() {
	enemy_->EnemyMove({-0.07f, 0.08f, -0.2f});
}