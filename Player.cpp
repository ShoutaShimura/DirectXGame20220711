#include "Player.h"
#include"RailCamera.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	
	worldTransform_.translation_ = { 0, 0, 50 };
}

void Player::Update()
{
	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
	});

	//�ړ�
	Move();

	//�L�����N�^�[�U������
	Attack();

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	debugText_->SetPos(50, 20);
	debugText_->Printf("Player localPos={%f,%f,%f}", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);

	Vector3 hoge;

	hoge = GetWorldPotision();

	debugText_->SetPos(50, 0);
	debugText_->Printf("Player worldPos={%f,%f,%f}",hoge.x, hoge.y, hoge.z);


	debugText_->SetPos(50, 40);
	debugText_->Printf("Player rotate={%f,%f,%f}", worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z);

}

void
Player::Draw(const ViewProjection& viewProjection)
{
	//3D���f����`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::Move()
{
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	const float speed = 0.5f;

	//�ړ��x�N�g����ύX���鏈��
	if (input_->PushKey(DIK_LEFT)) {
		move += { -speed, 0, 0 };
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move += { speed, 0, 0 };
	}

	if (input_->PushKey(DIK_UP)) {
		move += { 0, speed, 0 };
	}
	else if (input_->PushKey(DIK_DOWN)) {
		move += { 0, -speed, 0 };
	}

	if (input_->PushKey(DIK_W)) {
		move += { 0,0, speed};
	}
	else if (input_->PushKey(DIK_S)) {
		move += { 0,0, -speed };
	}

	//���W�ړ��i�x�N�g���̉��Z�j
	worldTransform_.translation_ += move;

	//�ړ����E���W
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 19;

	//�͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	Rotate();

	Matrix4 unit;
	unit.MatIdentity();
	worldTransform_.matWorld_ = unit;
	worldTransform_.matWorld_ = unit.MatCal(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
	
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	
	//�s��X�V
	worldTransform_.TransferMatrix();
}

void Player::Rotate()
{

	const float speed = 0.05f;

	//�ړ��x�N�g����ύX���鏈��
	if (input_->PushKey(DIK_U)) {
		worldTransform_.rotation_.y -= speed;
	}
	else if (input_->PushKey(DIK_I)) {
		worldTransform_.rotation_.y += speed;
	}


}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE)) {

		//�e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		Matrix4 mat;
		//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = mat.VecMat(velocity, worldTransform_.matWorld_);

		//�e�𐶐����A������
		//PlayerBullet* newBullet = new PlayerBullet();
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, GetWorldPotision(), velocity);

		//�e��o�^����
		bullets_.push_back(std::move(newBullet));
	}

}

Vector3 Player::GetWorldPotision()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];


	return worldPos;
}

Vector3 Player::GetWorldRotation()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;

	
	return worldPos;
	return Vector3();
}

void Player::OnCollision()
{
}
