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
/// 自キャラ
/// </summary>
class Player
{
public:
	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection>ビュープロジェクション（参照渡し）</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 旋回（回転）
	/// </summary>
	void Rotate();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	//ワールド座標を取得
	Vector3 GetWorldPotision();

	Vector3 GetWorldRotation();

	//衝突したら呼び出されるコールバック関数
	void OnCollision();

	//弾リストを取得
	const std::list < std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	const WorldTransform* SetWorldTransform(WorldTransform& worldtransform) { return worldTransform_.parent_ = &worldtransform; }

	void SetParentWorldTransform(const WorldTransform& railCameraWorldTransform) { worldTransform_.parent_ = &railCameraWorldTransform; }


private:

	//ワールド変換データ
	WorldTransform worldTransform_;

	Matrix4 worldPos;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//入力処理するため
	Input* input_ = nullptr;

	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;



};



