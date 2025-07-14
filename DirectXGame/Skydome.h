#pragma once
#include <KamataEngine.h>
#include <cassert>

using namespace KamataEngine;

class Skydome {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Camera* camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	~Skydome();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* modelSkydome_ = nullptr;

	// カメラ
	Camera* cameraSkydome_ = nullptr;

};
