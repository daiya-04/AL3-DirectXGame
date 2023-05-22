#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Skydome {
private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	//ViewProjection viewProjection_;

public:

	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);
};
