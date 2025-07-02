#pragma once
#include <KamataEngine.h>
#include "SceneManager.h"
#include "BaseScene.h"
#include "Player.h"

using namespace KamataEngine;

class GamePlayScene : public BaseScene {
public:

	/// <summary>
	/// 初期化関数
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw() override;

	~GamePlayScene();

private:

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライト
	Sprite* sprite_ = nullptr;

	// 3Dモデル
	Model* model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// カメラ
	Camera* camera_ = nullptr;

	// プレイヤー
	Player* player_ = nullptr;
};
