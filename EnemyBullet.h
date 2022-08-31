#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <assert.h>
#include "DebugText.h"

/// <summary>
/// �G�̒e
/// </summary>
class EnemyBullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="position">�������W</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V����</param>
	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }

	//�Փ˂�����Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	//���[���h���W���擾
	Vector3 GetWorldPotision();

private:

	WorldTransform worldTransform_;

	Model* model_=nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//���x
	Vector3 velocity_;

	//����<frm>
	static const int32_t kLifeTime = 60 * 5;

	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;

	//�f�X�t���O
	bool isDead_ = false;

	//�f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;
};

