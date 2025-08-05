#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include <cassert>
#include "SceneManager.h"

using namespace KamataEngine;

class TitleScene : public BaseScene {

	Model* playerModel_ = nullptr;

	// カメラ
	Camera* camera_ = nullptr;

	Player* player_ = nullptr;

	// 終了フラグ
	bool finished_ = false;

public :
	void Initialize();

	void Update();

	void Draw();

	// 終了フラグのゲッター
	bool InFinished() const { return finished_; }
};
