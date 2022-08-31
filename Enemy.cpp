#include "Enemy.h"
#include"Player.h"
#include"GameScene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(Model* model, const Vector3& position)
{
	//NULL�`�F�b�N
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("enemy.png");

	worldTransform_.translation_ = position;

	//�ڋ߃t�F�[�Y������
	ApproachReset();

	worldTransform_.Initialize();

}

void Enemy::Update()
{
	switch (phase_)
	{
	case Enemy::Phase::Approach:
	default:
		Approach();
		break;
	case Enemy::Phase::Leave:
		Leave();
		break;
	}
	
	//�s����X�V
	Matrix4 unit;
	unit.MatIdentity();
	worldTransform_.matWorld_ = unit;
	worldTransform_.matWorld_ = unit.MatCal(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	
}

void Enemy::Approach()
{
	//velocity_ = { 0,0,-0.1f };
	//�ړ�(�x�N�g�������Z)
	worldTransform_.translation_ += velocity_;

	//���˃^�C�}�[�J�E���g�_�E��
	fireTimer--;
	//�w�莞�ԂɒB����
	if (fireTimer <= 0) {
		//�e�𔭎�
		Fire();
		//���˃^�C�}�[��������
		fireTimer = kFireInterval;
	}
}

void Enemy::Leave()
{
	//�ړ�(�x�N�g�������Z)
	velocity_ = { 0.5f,0.5f,0 };
	worldTransform_.translation_ += velocity_;
}

void Enemy::Fire()
{
	assert(player_);

	//�e�̑��x
	const float baseSpeed = 1.0f;

	Vector3 playerPos = player_->GetWorldPotision();

	Vector3 enemyPos = GetWorldPotision();

	Vector3 v = playerPos - enemyPos;

	v = v.normalaize();

	Vector3 bVelocity = v * baseSpeed;

	Vector3 position = worldTransform_.translation_;

	//�e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_,position, bVelocity);

	//�e��o�^����
	gameScene_->AddEnemyBullet((std::move(newBullet)));

}

Vector3 Enemy::GetWorldPotision()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::ApproachReset()
{
	//���˃^�C�}�[��������
	fireTimer = kFireInterval;
}

void Enemy::OnCollision()
{
	isDead_ = true;
}
