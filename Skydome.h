#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

class Skydome {

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();


	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);
private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	
	//���f��
	Model* model_ = nullptr;

};