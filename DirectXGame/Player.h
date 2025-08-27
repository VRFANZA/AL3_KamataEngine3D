#pragma once
#include "WorldTransformUtil.h"
#include <KamataEngine.h>
#include <algorithm>
#include <cassert>
#include <numbers>
#include "MathUtils.h"

using namespace KamataEngine;
using namespace KamataEngine::MathUtils;

// 前方宣言
class MapChipField;

class Enemy;

class Player {

	// 左右の向き
	enum class LRDirection {
		kRight,
		kLeft
	};

	LRDirection lrDirection_ = LRDirection::kRight;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// カメラ
	Camera* camera_ = nullptr;

	// モデル
	Model* model_ = nullptr;

	// ワールドトランスフォーム更新クラス
	WorldTransformUtil* worldTransformUtil_ = nullptr;

	// テクスチャハンドル
	uint32_t textereHandle_ = 0;

	// 移動速度
	Vector3 velocity_ = {};

	// プレイヤーの当たり判定のサイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	// 当たり判定の構造体
	struct CollisionMapInfo {
		bool isHitCeiling_ = false; // 天井との判定
		bool onGround_ = false;     // 接地状態
		bool isHitWall_ = false;    // 壁との判定
		Vector3 displacement_;      // 移動量
	};

	// 4つの角の構造体
	enum Corner {
		kLeftTop,     // 左上
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kRightBottom, // 右下

		kNumCorner    //要素数

	};

	// 移動加速度
	static inline const float kAcceleration = 0.01f;

	// めり込み排除用の移動量
	static inline const float kBlank = 0.1f;

	// 移動減衰率
	static inline const float kAttenuation = 0.1f;

	// 最高速度制限値
	static inline const float kLimitRunSpeed = 0.5f;

	// 接地状態フラグ
	bool onGround_ = true;

	// 重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.98f / 60.0f;

	// 最大加速度
	static inline const float kLimitFallSpeed = 1.0f;

	// ジャンプ初速
	static inline const float kJumpAcceleration = 0.3f;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;

	// 旋回タイマー
	float turnTimer_ = 0.0f;

	// 旋回時間
	static inline const float kTimeTurn = 0.3f;

	// デスフラグ
	bool isDead_ = false;

	// クリアフラグ
	bool isClear_ = false;

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

	/// <summary>
	/// マップチップとの衝突
	/// </summary>
	/// <param name="info">衝突状態</param>
	void MapChipCollision(CollisionMapInfo& info);

	void IsCollisionUp(CollisionMapInfo& info);     // マップ衝突判定上方向
	void IsCollisionBottom(CollisionMapInfo& info); // マップ衝突判定下方向
	void IsCollisionLeft(CollisionMapInfo& info);   // マップ衝突判定左方向
	void IsCollisionRight(CollisionMapInfo& info);  // マップ衝突判定右方向

	void OnCollision(const Enemy* enemy);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// AABBを取得
	AABB GetAABB();

	// ③判定結果を反映して移動させる
	void ReflectCollisionResult(const CollisionMapInfo& info);

	// ④天井に接触している場合の処理
	void ProcessHitCeiling(const CollisionMapInfo& info);

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	// セッター
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	//ゲッターロボ
	const Vector3& GetVelocity() const { return velocity_; }

	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

	// クリアフラグのゲッターロボ
	bool IsClear() const { return isClear_; }

	~Player();

	// ワールド変換データ
	WorldTransform worldTransform_;
private :

};
