#pragma once
#include "Player.h"
#include <KamataEngine.h>
#include <algorithm>
#include "MathUtils.h"

using namespace KamataEngine;
using namespace KamataEngine::MathUtils;

// 矩形 インナークラスだと関数でスコープ外から参照できないらしいからグローバルに置いておく
struct Rect {
	float left = 0.0f;
	float right = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
};

class CameraController {
public:
	
	void Initialize(Camera* camera);

	void Update();

	void SetTarget(Player* target) { 
		target_ = target;
	}

	void SetMovableArea(Rect area) { movableArea_ = area; }

	void Reset();

private:

	// 追従対象の各方向へのカメラ移動制限（マージン）
	static inline const Rect kMargin = {
	    -30.0f, // 左マージン（負の値）
	    +30.0f, // 右マージン
	    -20.0f, // 下マージン（負の値）
	    +20.0f  // 上マージン
	};


	// カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};

	// カメラ
	Camera* camera_ = nullptr;

	// プレイヤー
	Player* target_ = nullptr;

	// 追従対象とカメラの座標の差(オフセット)
	Vector3 targetOffset_ = {0.0f, 0.0f, -15.0f};

	// カメラの目標座標
	Vector3 targetPosition_ = {};

	// 補間割合（1.0fなら即座に追従）
	static inline const float kInterpolationRate = 0.3f;

	//速度掛け率
	static inline const float kVelocityBias = 10.0f;

};
