#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

class Skydome {

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();


	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);
private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	
	//モデル
	Model* model_ = nullptr;

};