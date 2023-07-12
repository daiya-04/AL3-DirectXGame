#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"

class Ground {
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewProjection);

};
