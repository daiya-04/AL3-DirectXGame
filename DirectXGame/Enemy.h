#pragma once
#include "BaseCharacter.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Vec3.h"
#include "Matrix44.h"


class Enemy : public BaseCharacter{
private:

	std::vector<Model*> models_;

	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;

	float angle = 0.0f;

	Vec3 rotate;




public:

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(const ViewProjection& viewPrjection) override;

	const WorldTransform& GetWorldTransform() { return worldTransformBase_; }
	const WorldTransform& GetWorldTransformBody() { return worldTransformBody_; }

};
