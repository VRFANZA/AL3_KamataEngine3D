#pragma once
#include "MathUtils.h"
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include "MapChipField.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

using namespace KamataEngine;
using namespace KamataEngine::MathUtils;

class Enemy {
	
	WorldTransform worldTransform_;

	WorldTransformUtil* worldTransformUtil_ = nullptr;

	Camera* camera_ = nullptr;

	Model* model_ = nullptr;

	// 速度
	Vector3 velocity_ = {};

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// 歩行速度
	static inline const float kWalkSpeed = 0.03f;

	// 最初の角度
	static inline const float kWalkMotionAngleStart = 0.0f;

	// 最後の角度
	static inline const float kWalkMotionAngleEnd = 1.0f;

	// アニメーション周期(/s)
	static inline const float kWalkMotionTime = 3.0f;

	// 経過時間
	float walkTimer_ = 0.0f;

public:
	void Initialize(Model* model, Camera* camera, const Vector3& position);

	void Update();

	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
};
