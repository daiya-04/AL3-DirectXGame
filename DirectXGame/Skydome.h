#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"

class Skydome {
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewProjection);


};
