#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include "Input.h"

/// <summary>
/// ���[���J����
/// </summary>
class RailCamera{

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="position">�������W</param>
	/// <param name="rotation">�����p�x</param>
	void Initialize(const Vector3&position,const Vector3&rotation);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const WorldTransform& GetWorldMatrix() const { return worldTransform_; }

	

private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;


	//���͏������邽��
	Input* input_ = nullptr;
};