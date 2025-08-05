#pragma once
#include "MapChipField.h"
#include "MathUtils.h"
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

using namespace KamataEngine;
using namespace KamataEngine::MathUtils;

class Player;

class Enemy {

	// 敵の当たり判定のサイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

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

	void OnCollision(const Player* player);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// AABBを取得
	AABB GetAABB();
};
