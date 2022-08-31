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
	//NULLチェック
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("enemy.png");

	worldTransform_.translation_ = position;

	//接近フェーズ初期化
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
	
	//行列を更新
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
	//移動(ベクトルを加算)
	worldTransform_.translation_ += velocity_;

	//発射タイマーカウントダウン
	fireTimer--;
	//指定時間に達した
	if (fireTimer <= 0) {
		//弾を発射
		Fire();
		//発射タイマーを初期化
		fireTimer = kFireInterval;
	}
}

void Enemy::Leave()
{
	//移動(ベクトルを加算)
	velocity_ = { 0.5f,0.5f,0 };
	worldTransform_.translation_ += velocity_;
}

void Enemy::Fire()
{
	assert(player_);

	//弾の速度
	const float baseSpeed = 1.0f;

	Vector3 playerPos = player_->GetWorldPotision();

	Vector3 enemyPos = GetWorldPotision();

	Vector3 v = playerPos - enemyPos;

	v = v.normalaize();

	Vector3 bVelocity = v * baseSpeed;

	Vector3 position = worldTransform_.translation_;

	//弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_,position, bVelocity);

	//弾を登録する
	gameScene_->AddEnemyBullet((std::move(newBullet)));

}

Vector3 Enemy::GetWorldPotision()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::ApproachReset()
{
	//発射タイマーを初期化
	fireTimer = kFireInterval;
}

void Enemy::OnCollision()
{
	isDead_ = true;
}
