#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Player {
private:

	//ワールド変換座標
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="vewProjection">ビュープロジェクション (参照渡し)</param>
	void Draw(ViewProjection& vewProjection);

};
