#pragma once
#include "SceneManager.h"
#include "BaseScene.h"

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
};
