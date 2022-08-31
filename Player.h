#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "Input.h"
#include "DebugText.h"
#include "Matrix4.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>



/// <summary>
/// ���L����
/// </summary>
class Player
{
public:
	Player();
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection>�r���[�v���W�F�N�V�����i�Q�Ɠn���j</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// ����i��]�j
	/// </summary>
	void Rotate();

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	//���[���h���W���擾
	Vector3 GetWorldPotision();

	Vector3 GetWorldRotation();

	//�Փ˂�����Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	//�e���X�g���擾
	const std::list < std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	const WorldTransform* SetWorldTransform(WorldTransform& worldtransform) { return worldTransform_.parent_ = &worldtransform; }

	void SetParentWorldTransform(const WorldTransform& railCameraWorldTransform) { worldTransform_.parent_ = &railCameraWorldTransform; }


private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	Matrix4 worldPos;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//���͏������邽��
	Input* input_ = nullptr;

	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;



};



