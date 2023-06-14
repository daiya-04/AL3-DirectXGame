#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <fstream>
#include <cassert>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete modelSkydome_;
	delete debugCamera_;
	delete player_;
	for (PlayerBullet* bullet : playerBullets_) {
		delete bullet;
	}
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	delete skydome_;
	delete railCamera_;
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	PlayertextureHandle_ = TextureManager::Load("mario.jpg");
	EnemyTextureHandle_ = TextureManager::Load("Monster.png");
	TextureManager::Load("Reticle.png");

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
	player_->SetGameScene(this);
	//// 敵キャラの生成
	//Enemy* enemy_ = new Enemy();
	//// 敵キャラの初期化
	//enemy_->Initialize(model_, EnemyTextureHandle_, {30.0f, 2.0f, 40.0f});
	//// 敵キャラに自キャラのアドレスを渡す
	//enemy_->SetPlayer(player_);
	//enemy_->SetGameScene(this);
	//enemies_.push_back(enemy_);
	//スカイドームの生成
	skydome_ = new Skydome();
	//スカイドームの初期化
	skydome_->Initialize(modelSkydome_);

	LoadEnemyPopData();
	

	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {

	UpdateEnemyPopCommand();
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	playerBullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	enemies_.remove_if([](Enemy* enemy) {
		if (enemy->isDead()) {
			delete enemy;
			return true;
		}
		return false;
	});

	player_->Update(viewProjection_);
	// 弾の更新
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Update();
	}

	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}
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
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Draw(viewProjection_);
	}
	for (Enemy* enemy : enemies_) {
		enemy->Draw(viewProjection_);
	}
	
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}
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

	player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollision() {

	//判定対象AとBの座標
	Vector3 posA, posB;

	
	

	#pragma region 自キャラと敵弾の当たり判定
	//自キャラの座標
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets_) {
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
	
	
	for (Enemy* enemy : enemies_) {
		posA = enemy->GetWorldPosition();
		for (PlayerBullet* bullet : playerBullets_) {
			// 自キャラの座標
			posB = bullet->GetWorldPosition();
			float length = Length(Sub(posA, posB));
			if (length <= 2) {
				enemy->OnCollision();
				bullet->OnCollision();
			}
		}
	}
	
	#pragma endregion

	#pragma region 自弾と敵弾の当たり判定
	for (PlayerBullet* bulletA : playerBullets_) {
		for (EnemyBullet* bulletB : enemyBullets_) {
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

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { 
	enemyBullets_.push_back(enemyBullet); 
}

void GameScene::AddPlayerBullet(PlayerBullet* playerBullet) {
	playerBullets_.push_back(playerBullet);
}

void GameScene::EnemyPop(Vector3 vector) {
	// 敵キャラの生成
	Enemy* enemy_ = new Enemy();
	// 敵キャラの初期化
	enemy_->Initialize(model_, EnemyTextureHandle_, vector);
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	enemy_->SetGameScene(this);
	enemies_.push_back(enemy_);
}

void GameScene::LoadEnemyPopData() {

	std::ifstream file;
	file.open("./Resources/enemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();
}

void GameScene::UpdateEnemyPopCommand() {
	// 待機処理
	if (waitintFlag) {
		waitingTimer--;
		if (waitingTimer < 0) {
			waitintFlag = false;
		}
		return;
	}

	//1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(enemyPopCommands, line)) {

		


		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}

		//POPコマンド
		if (word.find("POP") == 0) {
			//x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			//y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			//z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			//敵を発生させる
			EnemyPop({x, y, z});

		} else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			waitintFlag = true;
			waitingTimer = waitTime;

			//コマンドループを抜ける
			break;
		}


	}

}