#pragma once
#include "BaseScene.h"
#include "Fade.h"
#include "Player.h"
#include "SceneManager.h"
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include <cassert>

using namespace KamataEngine;

class ClearScene {
	Model* playerModel_ = nullptr;

	// カメラ
	Camera* camera_ = nullptr;

	Player* player_ = nullptr;

	// 終了フラグ
	bool finished_ = false;

	Fade* fade_ = nullptr;

public:
	// シーンのフェーズ
	enum class Phase { kFadeIn, kMain, kFadeOut };

	// フェーズの初期化
	Phase phase_ = Phase::kFadeIn;

	void Initialize();

	void Update();

	void Draw();

	~ClearScene();

	// 終了フラグのゲッター
	bool InFinished() const { return finished_; }
};
