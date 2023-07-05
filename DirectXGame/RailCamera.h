#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"


class RailCamera {
private:

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

public:

	void Initialize(ViewProjection camera);

	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldMatrix() { return worldTransform_; }

};
