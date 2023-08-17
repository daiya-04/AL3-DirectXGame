#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"
#include "BaseCharacter.h"
#include <optional>



class Player : public BaseCharacter{
private:

	enum class Behavior {
		kRoot,   // 通常状態
		kAttack, // 攻撃中
	};

	//ワールド変換座標
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	WorldTransform worldTransformWeapon_;

	//モデル
	//Model* modelBody_ = nullptr;
	//Model* modelHead_ = nullptr;
	//Model* modelL_arm_ = nullptr;
	//Model* modelR_arm_ = nullptr;
	std::vector<Model*> models_ = {nullptr};

	Input* input_ = nullptr;

	const ViewProjection* viewProjection_ = nullptr;

	Behavior behavior_ = Behavior::kRoot;

	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	Vec3 rotate;

	float floatingParameter_ = 0.0f;

	float num = 0.0f;

	// 浮遊の振幅
	float amplitude = 0.5f;
	// 浮遊移動のサイクル<frame>
	int cycle = 60;

	int count = 0;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::vector<Model*>& models)override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="vewProjection">ビュープロジェクション (参照渡し)</param>
	void Draw(const ViewProjection& vewProjection)override;
	/// <summary>
	/// 浮遊ギミック初期化
	/// </summary>
	void InitializeFloatingGimmick();
	/// <summary>
	/// 浮遊ギミック更新
	/// </summary>
	void UpdateFloatingGimmick();
	//通常行動初期化
	void BehaviorRootInitialize();
	//攻撃行動初期化
	void BehaviorAttackInitialize();
	//通常行動更新
	void BehaviorRootUpdate();
	//攻撃行動更新
	void BehaviorAttackUpdate();
	//調整項目の適用
	void ApplyGlobalVariables();

	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection; }

	const WorldTransform& GetWorldTransform() { return worldTransformBase_; }
	const WorldTransform& GetWorldTransformBody() { return worldTransformBody_; }
	//const WorldTransform& GetWorldTransformHead() { return worldTransformHead_; }
	//const WorldTransform& GetWorldTransformL_arm() { return worldTransformL_arm_; }
	//const WorldTransform& GetWorldTransformR_arm() { return worldTransformR_arm_; }

};
