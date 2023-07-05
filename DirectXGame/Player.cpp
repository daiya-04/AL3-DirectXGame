#include "Player.h"
#include "ImGuiManager.h"
#include "GameScene.h"
#include <assert.h>

Player::~Player() { 
	delete sprite2DReticle;
}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 0.0f, 30.0f};
	input_=Input::GetInstance();
	worldTransform3Dreticle_.Initialize();

	uint32_t textureReticle = TextureManager::Load("Reticle.png");
	sprite2DReticle = Sprite::Create(
	    textureReticle,
	    {640.0f,360.0f},
	    {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}
	);
}

void Player::Update(ViewProjection viewProjection) {
	
	Vector2 spritePos = sprite2DReticle->GetPosition();
	XINPUT_STATE joyState;

	//キャラクターの移動ベクトル
	Vec3 move = {};
	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.5f;
	const float kRotSpeed = 0.02f;
	

	//プレイヤー移動
	/*if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}*/

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}
	//プレイヤー旋回
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
	//レティクル移動
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	
		spritePos.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 10.0f;
		spritePos.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 10.0f;

		sprite2DReticle->SetPosition(spritePos);
	}

	//プレイヤー攻撃
	Attack();

	worldTransform_.translation_ += move;

	const float kMoveLimitX = 20;
	const float kMoveLimitY = 11;
	//移動の制限
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	

	worldTransform_.UpdateMatrix();

	

	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3Dreticle = 50.0f;
	Vec3 offset = {0.0f, 0.0f, 1.0f};
	offset = TransformNormal(offset, worldTransform_.matWorld_);
	offset = kDistancePlayerTo3Dreticle * offset.Normalize();
	worldTransform3Dreticle_.translation_ = {
	    GetWorldPosition().x + offset.x, GetWorldPosition().y + offset.y,
	    GetWorldPosition().z + offset.z
	};

	worldTransform3Dreticle_.UpdateMatrix();

	/*Vector3 positionReticle = {
	    worldTransform3Dreticle_.matWorld_.m[3][0],
		worldTransform3Dreticle_.matWorld_.m[3][1],
	    worldTransform3Dreticle_.matWorld_.m[3][2]
	};*/

	Matrix4x4 viewportMatrix =
	    MakeViewportMatrix(0.0f, 0.0f, WinApp::kWindowWidth, WinApp::kWindowHeight);

	Matrix4x4 VPVMatrix =
	    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), viewportMatrix);

	//positionReticle = Transform(positionReticle, VPVMatrix);

	//sprite2DReticle->SetPosition(Vector2(positionReticle.x, positionReticle.y));

	/*POINT mousePosition;

	GetCursorPos(&mousePosition);

	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	sprite2DReticle->SetPosition(Vector2(float(mousePosition.x), float(mousePosition.y)));*/

	Matrix4x4 InverseVPVMatrix = Inverse(VPVMatrix);

	Vec3 PosNear = Vec3(float(spritePos.x), float(spritePos.y), 0.0f);
	Vec3 PosFar = Vec3(float(spritePos.x), float(spritePos.y), 1.0f);

	PosNear = Transform(PosNear, InverseVPVMatrix);
	PosFar = Transform(PosFar, InverseVPVMatrix);

	Vec3 Direction = PosFar - PosNear;
	
	Direction = Direction.Normalize();

	const float kDistanceTestObject = kDistancePlayerTo3Dreticle;
	
	worldTransform3Dreticle_.translation_ = {
	    PosNear.x + Direction.Normalize().x * kDistanceTestObject,
	    PosNear.y + Direction.Normalize().y * kDistanceTestObject,
	    PosNear.z + Direction.Normalize().z * kDistanceTestObject
	};

	worldTransform3Dreticle_.UpdateMatrix();

#ifdef _DEBUG
	ImGui::Begin("Player");
	ImGui::Text(
	    "Position\n%.02f %.02f %.02f\nRatate\n%.02f", worldTransform_.translation_.x,
	    worldTransform_.translation_.y, worldTransform_.translation_.z,
	    worldTransform_.rotation_.y);
	ImGui::Text(
	    "2DReticle:(%f,%f)", sprite2DReticle->GetPosition().x, sprite2DReticle->GetPosition().y);
	//ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", PosNear.x, PosNear.y, PosNear.z);
	//ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", PosFar.x, PosFar.y, PosFar.z);
	/*ImGui::Text(
	    "3DReticle:(%+.2f,%+.2f,%+.2f)", worldTransform3Dreticle_.translation_.x,
	    worldTransform3Dreticle_.translation_.y, worldTransform3Dreticle_.translation_.z);*/

	ImGui::End();
#endif

}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//model_->Draw(worldTransform3Dreticle_, viewProjection);
}

void Player::DrawUI() {
	sprite2DReticle->Draw();
}

void Player::Attack() {

	XINPUT_STATE joyState;

	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}

	if (joyState.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER) {

		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vec3 velocity(0, 0, kBulletSpeed);

		Vec3 WorldPos3DRetivle = {
		    worldTransform3Dreticle_.matWorld_.m[3][0],
		    worldTransform3Dreticle_.matWorld_.m[3][1],
		    worldTransform3Dreticle_.matWorld_.m[3][2],
		};

		velocity = WorldPos3DRetivle - GetWorldPosition();
		velocity = kBulletSpeed * velocity.Normalize();

		//弾の生成と初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);
		//弾を登録する
		gameScene_->AddPlayerBullet(newBullet);
	} 

}

void Player::OnCollision() {

}

Vec3 Player::GetWorldPosition() {

	Vec3 WorldPos;

	WorldPos.x = worldTransform_.matWorld_.m[3][0];
	WorldPos.y = worldTransform_.matWorld_.m[3][1];
	WorldPos.z = worldTransform_.matWorld_.m[3][2];

	return WorldPos;
}



void Player::SetParent(const WorldTransform* parent) { 
	worldTransform_.parent_ = parent;
}