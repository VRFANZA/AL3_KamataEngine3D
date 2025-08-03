#pragma once
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include <algorithm>
#include <cassert>
#include <numbers>
#include "MathUtils.h"

using namespace KamataEngine;
using namespace KamataEngine::MathUtils;

class Player {
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

	const Vector3& GetVelocity() const { return velocity_; }

	~Player();

	// ワールド変換データ
	WorldTransform worldTransform_;
private :

	// 左右の向き
	enum class LRDirection {
		kRight,
		kLeft
	};

	LRDirection lrDirection_ = LRDirection::kRight;


	// カメラ
	Camera* camera_ = nullptr;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textereHandle_ = 0;

	// ワールドトランスフォーム更新クラス
	WorldTransformUtil* worldTransformUtil_ = nullptr;

	// 移動速度
	Vector3 velocity_ = {};

	// 移動加速度
	static inline const float kAcceleration = 0.01f;

	// 移動減衰率
	static inline const float kAttenuation = 0.05f;

	// 最高速度制限値
	static inline const float kLimitRunSpeed = 1.0f;

	// 接地状態フラグ
	bool onGround_ = true;

	// 重力加速度(下方向)
	static inline const float kGravityAcceleration = 9.8f / 60.0f;

	// 最大加速度
	static inline const float kLimitFallSpeed = 2.0f;

	// ジャンプ初速
	static inline const float kJumpAcceleration = 1.0f;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;

	// 旋回タイマー
	float turnTimer_ = 0.0f;

	// 旋回時間
	static inline const float kTimeTurn = 0.3f;
};
