#pragma once
#include "MathUtils.h"
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include <algorithm>
#include <cassert>
#include <numbers>
#include <array>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

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

	// 存続時間(/s)
	static inline const float kDuration = 1.5f;

	// 移動の速さ
	static inline const float kSpeed = 0.05f;

	// 分割した1つ分の角度
	static inline const float kAngleUnit = static_cast<float>((2 * M_PI) / kNumberOfParticles);

	std::array<WorldTransform, kNumberOfParticles> worldTransforms_;

	// 色変更オブジェクト
	ObjectColor objectColor_;

	// 色の数値
	Vector4 color_ = {1, 1, 1, 1};

	// 終了フラグ
	bool isFinished_ = false;

	// 経過時間カウント
	float counter_ = 0.0f;

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

	bool InFinished() const { return isFinished_; }

	inline Matrix4x4 MakeRotationMatrixZ(const float& rotation) {
		// Zの回転行列
		Matrix4x4 rotateMatrixZ;
		rotateMatrixZ.m[0][0] = cosf(rotation);
		rotateMatrixZ.m[0][1] = sinf(rotation);
		rotateMatrixZ.m[0][2] = 0.0f;
		rotateMatrixZ.m[0][3] = 0.0f;

		rotateMatrixZ.m[1][0] = -sinf(rotation);
		rotateMatrixZ.m[1][1] = cosf(rotation);
		rotateMatrixZ.m[1][2] = 0.0f;
		rotateMatrixZ.m[1][3] = 0.0f;

		rotateMatrixZ.m[2][0] = 0.0f;
		rotateMatrixZ.m[2][1] = 0.0f;
		rotateMatrixZ.m[2][2] = 1.0f;
		rotateMatrixZ.m[2][3] = 0.0f;

		rotateMatrixZ.m[3][0] = 0.0f;
		rotateMatrixZ.m[3][1] = 0.0f;
		rotateMatrixZ.m[3][2] = 0.0f;
		rotateMatrixZ.m[3][3] = 1.0f;

		return rotateMatrixZ;
	}

	// 行列をベクトルに変換する関数
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

};
