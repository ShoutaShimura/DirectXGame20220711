#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>
#include "DebugText.h"
#include "EnemyBullet.h"
#include <memory> 
#include <list>

//自機クラスの前方宣言
class Player;
class GameScene;

/// <summary>
/// 敵
/// </summary>
class Enemy
{
public:
	Enemy();
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	void Approach();
	void Leave();

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	void SetPlayer(Player* player) { player_ = player; }

	void SetGameScene(GameScene* gamescene) {gameScene_ = gamescene; }

	bool IsDead() const { return isDead_; }

	//ワールド座標を取得
	Vector3 GetWorldPotision();

	//接近フェーズ初期化
	void ApproachReset();

	//衝突したら呼び出されるコールバック関数
	void OnCollision();

	

public:

	//発射間隔
	static const int kFireInterval = 60;

private:



	//発射タイマー
	int32_t fireTimer = 0;

	

	//ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//速度
	Vector3 velocity_;

	//行動フェーズ
	enum class Phase {
		Approach,//接近する
		Leave,//離脱する
	};

	//フェーズ
	Phase phase_ = Phase::Approach;

	//自キャラ
	Player* player_ = nullptr;
	GameScene* gameScene_ = nullptr;

	//デスフラグ
	bool isDead_ = false;


};

