#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"

class Player {
private:

	//ワールド変換座標
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	//モデル
	Model* modelBody_ = nullptr;
	Model* modelHead_ = nullptr;
	Model* modelL_arm_ = nullptr;
	Model* modelR_arm_ = nullptr;

	Input* input_ = nullptr;

	const ViewProjection* viewProjection_ = nullptr;

	Vec3 rotate;

	float floatingParameter_ = 0.0f;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* modelBody,Model* modelHead,Model* modelL_arm,Model* modelR_arm);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="vewProjection">ビュープロジェクション (参照渡し)</param>
	void Draw(ViewProjection& vewProjection);
	/// <summary>
	/// 浮遊ギミック初期化
	/// </summary>
	void InitializeFloatingGimmick();

	void UpdateFloatingGimmick();

	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection; }

	const WorldTransform& GetWorldTransform() { return worldTransformBase_; }
	const WorldTransform& GetWorldTransformBody() { return worldTransformBody_; }
	//const WorldTransform& GetWorldTransformHead() { return worldTransformHead_; }
	//const WorldTransform& GetWorldTransformL_arm() { return worldTransformL_arm_; }
	//const WorldTransform& GetWorldTransformR_arm() { return worldTransformR_arm_; }

};
