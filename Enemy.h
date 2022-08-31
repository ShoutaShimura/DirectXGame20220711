#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>
#include "DebugText.h"
#include "EnemyBullet.h"
#include <memory> 
#include <list>

//���@�N���X�̑O���錾
class Player;
class GameScene;

/// <summary>
/// �G
/// </summary>
class Enemy
{
public:
	Enemy();
	~Enemy();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="position">�������W</param>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V����</param>
	void Draw(const ViewProjection& viewProjection);

	void Approach();
	void Leave();

	/// <summary>
	/// �e����
	/// </summary>
	void Fire();

	void SetPlayer(Player* player) { player_ = player; }

	void SetGameScene(GameScene* gamescene) {gameScene_ = gamescene; }

	bool IsDead() const { return isDead_; }

	//���[���h���W���擾
	Vector3 GetWorldPotision();

	//�ڋ߃t�F�[�Y������
	void ApproachReset();

	//�Փ˂�����Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	

public:

	//���ˊԊu
	static const int kFireInterval = 60;

private:



	//���˃^�C�}�[
	int32_t fireTimer = 0;

	

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//���x
	Vector3 velocity_;

	//�s���t�F�[�Y
	enum class Phase {
		Approach,//�ڋ߂���
		Leave,//���E����
	};

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;

	//���L����
	Player* player_ = nullptr;
	GameScene* gameScene_ = nullptr;

	//�f�X�t���O
	bool isDead_ = false;


};

