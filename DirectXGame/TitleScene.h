#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include <cassert>
#include "SceneManager.h"
#include "Fade.h"

using namespace KamataEngine;

class TitleScene : public BaseScene {

	Model* playerModel_ = nullptr;

	// カメラ
	Camera* camera_ = nullptr;

	Player* player_ = nullptr;

	// 終了フラグ
	bool finished_ = false;

	Fade* fade_ = nullptr;

public :

	// シーンのフェーズ
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut
	};

	// フェーズの初期化
	Phase phase_ = Phase::kFadeIn;

	void Initialize();

	void Update();

	void Draw();

	~TitleScene();

	// 終了フラグのゲッター
	bool InFinished() const { return finished_; }
};
