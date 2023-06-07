#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete modelSkydome_;
	delete debugCamera_;
	delete player_;
	delete enemy_;
	delete skydome_;
	delete railCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	PlayertextureHandle_ = TextureManager::Load("mario.jpg");
	EnemyTextureHandle_ = TextureManager::Load("Monster.png");

	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	
	
	viewProjection_.Initialize();

	railCamera_ = new RailCamera();
	railCamera_->Initialize(viewProjection_);

	

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, PlayertextureHandle_);
	player_->SetParent(&railCamera_->GetWorldMatrix());
	// 敵キャラの生成
	enemy_ = new Enemy();
	// 敵キャラの初期化
	enemy_->Initialize(model_, EnemyTextureHandle_);
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	//スカイドームの生成
	skydome_ = new Skydome();
	//スカイドームの初期化
	skydome_->Initialize(modelSkydome_);

	
	

	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	player_->Update();
	enemy_->Update();
	skydome_->Update();
	CheckAllCollision();

	railCamera_->Update();

	viewProjection_.matView = railCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

	

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = true;
	}
#endif // DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

	}

	viewProjection_.TransferMatrix();
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
	enemy_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);

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

void GameScene::CheckAllCollision() {

	//判定対象AとBの座標
	Vector3 posA, posB;

	//自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	#pragma region 自キャラと敵弾の当たり判定
	//自キャラの座標
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets) {
		//敵弾の座標
		posB = bullet->GetWorldPosition();
		float length = Length(Sub(posA, posB));
		if (length<=2) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定
	posA = enemy_->GetWorldPosition();

	for (PlayerBullet* bullet : playerBullets) {
		//自キャラの座標
		posB = bullet->GetWorldPosition();
		float length = Length(Sub(posA, posB));
		if (length <= 2) {
			enemy_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region 自弾と敵弾の当たり判定
	for (PlayerBullet* bulletA : playerBullets) {
		for (EnemyBullet* bulletB : enemyBullets) {
			posA = bulletA->GetWorldPosition();
			posB = bulletB->GetWorldPosition();
			float length = Length(Sub(posA, posB));
			if (length <= 2) {
				bulletA->OnCollision();
				bulletB->OnCollision();
			}
		}
	}
	#pragma endregion
}