#pragma once
#include "MathUtils.h"
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include "MapChipField.h"

using namespace KamataEngine;
using namespace KamataEngine::MathUtils;

class Enemy {
	
	WorldTransform worldTransform_;

	WorldTransformUtil* worldTransformUtil_ = nullptr;

	Camera* camera_ = nullptr;

	Model* model_ = nullptr;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// 歩行速度
	static inline const float kWalkSpeed = 0.03f;

	// 速度
	Vector3 velocity_ = {};

public:
	void Initialize(Model* model, Camera* camera, const Vector3& position);

	void Update();

	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
};
