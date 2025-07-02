#pragma once
#include <KamataEngine.h>
#include <cassert>

using namespace KamataEngine;

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model,uint32_t textureHandle,Camera* camera);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	~Player();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// カメラ
	Camera* camera_ = nullptr;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textereHandle_ = 0;
};
