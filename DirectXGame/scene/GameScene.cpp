#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "imgui.h"

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("mario.jpg");

	viewProjection_.Initialize();

	debugCamera_ = std::make_unique<DebugCamera>(WinApp::kWindowWidth,WinApp::kWindowHeight);

	modelPlayerBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelPlayerHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelPlayerL_arm_.reset(Model::CreateFromOBJ("float_L_Arm", true));
	modelPlayerR_arm_.reset(Model::CreateFromOBJ("float_R_Arm", true));

	skydomeModel_.reset(Model::CreateFromOBJ("skydome",true));
	groundModel_.reset(Model::CreateFromOBJ("ground", true));

	player_ = std::make_unique<Player>();
	player_->Initialize(modelPlayerBody_.get(), modelPlayerHead_.get(), modelPlayerL_arm_.get(), modelPlayerR_arm_.get());

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(skydomeModel_.get());

	ground_ = std::make_unique<Ground>();
	ground_->Initialize(groundModel_.get());

	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(&followCamera_->GetViewProjection());

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するViewProjectionを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {

	player_->Update();
	skydome_->Update();
	ground_->Update();
	followCamera_->Update();

	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = true;
	}
#endif // DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.TransferMatrix();
	}
	
	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
