#include "Skydome.h"

void Skydome::Initialize(Model* model, const Vector3& position)
{
	//NULL�`�F�b�N
	assert(model);

	model_ = model;

	worldTransform_.translation_ = position;

	worldTransform_.scale_ = { 1000,1000,1000 };

	worldTransform_.Initialize();
}

void Skydome::Update()
{
	//�s����X�V
	Matrix4 unit;
	unit.MatIdentity();
	worldTransform_.matWorld_ = unit;
	worldTransform_.matWorld_ = unit.MatCal(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}

void Skydome::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
