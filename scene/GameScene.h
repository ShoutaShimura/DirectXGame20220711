#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"
#include <memory>
#include <list>
#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	void EnemyBulletUpdate();
	void EnemyBulletDraw();

	//敵発生コマンド
	std::stringstream enemyPopCommands;

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();


	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCpmmands();

	void EnemyBorn(const Vector3& position);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//3Dモデル
	Model* model_ = nullptr;

	Model* modelSkydome_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	//自キャラ
	Player* player_ = nullptr;

	//敵
	Enemy* enemy_ = nullptr;

	//天球
	Skydome* skydome_ = nullptr;

	RailCamera* railCamera_ = nullptr;

	Vector3 velocty;

	WorldTransform worldTransform_;
	WorldTransform EworldTransform_;
	WorldTransform SkyworldTransform_;
	WorldTransform railWorldTransform_;

	const float playerSize = 1;
	const float enemySize = 1;

	//敵弾リスト
	std::list<std::unique_ptr<EnemyBullet>> eBullets_;

	//敵リスト
	std::list<std::unique_ptr<Enemy>> enemys_;


	//発射間隔
	static const int kFireInterval = 60;

	//発射タイマー
	int32_t fireTimer = 0;

	bool isWait = false;

	int32_t waitTimer = 0;

public:
	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet>enemyBullet);

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	//デバッグカメラ有効
	bool isDebugcameraActive_ = false;
};
