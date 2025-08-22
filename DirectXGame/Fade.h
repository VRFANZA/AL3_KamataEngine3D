#pragma once
#include <KamataEngine.h>
#include <algorithm>

using namespace KamataEngine;

class Fade {

	// フェードの効果時間
	float duration_ = 0.0f;

	// 経過時間
	float counter_ = 0.0f;

	Sprite* sprite_ = nullptr;

	uint32_t fadeTexture = 0;

	Vector2 position_ = {0, 0};

	Vector2 size_ = {1280, 720};

	Vector4 color_ = {0, 0, 0, 1};

	Vector2 anchorpoint_ = {0.0f, 0.0f};
	
	bool isFlipX_ = false;
	bool isFlipY_ = false;

public:
	
	// フェードの状態
	enum class Status {
		None,    // フェードなし
		FadeIn,  // フェードイン
		FadeOut, // フェードアウト
	};

	// フェード状態を無しで初期化
	Status status_ = Status::None;

	void Start(Status status, float duration);

	void Stop();

	// フェード終了判定
	bool IsFinished() const;

	void Initialize();

	void Update();

	void Draw();

};
