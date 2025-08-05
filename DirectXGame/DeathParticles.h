#pragma once
#include "MathUtils.h"
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include <algorithm>
#include <cassert>
#include <numbers>
#include <array>

using namespace KamataEngine;
using namespace KamataEngine::MathUtils;

class DeathParticles {

	// カメラ
	Camera* camera_ = nullptr;

	// モデル
	Model* model_ = nullptr;

	// ワールドトランスフォーム更新クラス
	WorldTransformUtil* worldTransformUtil_ = nullptr;

	static inline const uint32_t kNumberOfParticles = 8;

	std::array<WorldTransform, kNumberOfParticles> worldTransforms_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Camera* camera, const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

};
