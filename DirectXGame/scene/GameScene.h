#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "PlayerBullet.h"
#include "Skydome.h"
#include "RailCamera.h"
#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

    /// <summary>
    /// 衝突判定と応答
    /// </summary>
	void CheckAllCollision();

    /// <summary>
    /// 敵弾を追加する
    /// </summary>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

    /// <summary>
    /// 自弾を追加する
    /// </summary>
	void AddPlayerBullet(PlayerBullet* playerbullet);
	
	/// <summary>
	/// 敵を発生させる
	/// </summary>
	void EnemyPop(Vec3 vector);

    /// <summary>
    /// 敵発生データの読み込み
    /// </summary>
	void LoadEnemyPopData();

    /// <summary>
    /// 敵発生のコマンドの更新
    /// </summary>
	void UpdateEnemyPopCommand();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;

	Player* player_ = nullptr;
	std::list<PlayerBullet*> playerBullets_;
	std::list<Enemy*> enemies_;
	std::list<EnemyBullet*> enemyBullets_;
	Skydome* skydome_ = nullptr;
	RailCamera* railCamera_ = nullptr;

	uint32_t PlayertextureHandle_ = 0;
	uint32_t EnemyTextureHandle_ = 0;
	
	
	ViewProjection viewProjection_;

	DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;

	std::stringstream enemyPopCommands;
	bool waitintFlag = false;
	int waitingTimer;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
