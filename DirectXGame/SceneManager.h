#pragma once
#include "BaseScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include "ClearScene.h"
#include <memory>

class SceneManager {

public:

	enum Scene {
		TITLE,
		GAME,
		Clear,
	};

	/// <summary>
	/// シーン切り替え関数
	/// </summary>
	/// <param name="scene">切り替え先のシーン</param>
	static void ChangeScene(Scene scene);

	/// <summary>
	/// 更新関数
	/// </summary>
	static void Update();

	/// <summary>
	/// 描画関数
	/// </summary>
	static void Draw();

private:
	static BaseScene* nowScene_;

};
