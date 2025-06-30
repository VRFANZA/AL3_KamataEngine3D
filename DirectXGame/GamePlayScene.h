#pragma once
#include <KamataEngine.h>
#include "SceneManager.h"
#include "BaseScene.h"

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

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GamePlayScene();

private:
	// ImGuiで値を入力する変数
	float inputFloat3[3] = {0.0f, 0.0f, 0.0f};

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	
	// サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;

	// スプライト
	Sprite* sprite_ = nullptr;

	// 3Dモデル
	Model* model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// カメラ
	Camera camera_;

	// デバッグカメラ
	DebugCamera* debugcamela_ = nullptr;
};
