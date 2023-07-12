#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {

	matWorld_ = Matrix44::MakeAffinMatrix(scale_, rotation_, translation_);

	if (parent_) {
		matWorld_ = matWorld_ * parent_->matWorld_;
	}

	TransferMatrix();
}