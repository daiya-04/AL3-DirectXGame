#include "Player.h"
#include "ImGuiManager.h"
#include <assert.h>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransForm_.Initialize();
	input_=Input::GetInstance();
}

void Player::Update() {
	
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	const float kRotSpeed = 0.02f;

	//プレイヤー移動
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	//プレイヤー旋回
	if (input_->PushKey(DIK_A)) {
		worldTransForm_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransForm_.rotation_.y += kRotSpeed;
	}
	//プレイヤー攻撃
	Attack();

	//弾の更新
	if (bullet_) {
		bullet_->Update();
	}

	worldTransForm_.translation_ = Add(worldTransForm_.translation_, move);

	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;
	//移動の制限
	worldTransForm_.translation_.x = max(worldTransForm_.translation_.x, -kMoveLimitX);
	worldTransForm_.translation_.x = min(worldTransForm_.translation_.x, +kMoveLimitX);
	worldTransForm_.translation_.y = max(worldTransForm_.translation_.y, -kMoveLimitY);
	worldTransForm_.translation_.y = min(worldTransForm_.translation_.y, +kMoveLimitY);

	worldTransForm_.UpdateMatrix();

	
	ImGui::Begin("debug");
	ImGui::Text(
	    "%.02f %.02f %.02f\n%.02f", worldTransForm_.translation_.x, worldTransForm_.translation_.y,
	    worldTransForm_.translation_.z, worldTransForm_.rotation_.y);
	ImGui::End();


}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransForm_, viewProjection, textureHandle_);

	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {

		//弾の生成と初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransForm_.translation_);
		//弾を登録する
		bullet_ = newBullet;

	} 

}