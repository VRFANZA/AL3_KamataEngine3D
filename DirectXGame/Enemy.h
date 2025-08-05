#pragma once
#include "MathUtils.h"
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include "MapChipField.h"

using namespace KamataEngine;

class Enemy {
	
	WorldTransform worldTransform_;

	WorldTransformUtil* worldTransformUtil_ = nullptr;

	Camera* camera_ = nullptr;

	Model* model_ = nullptr;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

public:
	void Initialize(Model* model, Camera* camera, const Vector3& position);

	void Update();

	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
};
