#define NOMINMAX
#include "Player.h"
#include "Enemy.h"
#include "MapChipField.h"

void Player::Initialize(Model* model, Camera* camera, const Vector3& position) {
	// NULLチェック
	assert(model);
	assert(camera);

	model_ = model;
	camera_ = camera;

	// ワールドトランスフォーム更新クラスの生成
	worldTransformUtil_ = new WorldTransformUtil();

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// モデルをy軸回りにπ/2(90°)回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() {

	//=============
	// 移動入力
	//=============
	// 接地確認
	if (onGround_) {

		// 接地時のみ左右移動操作可能

		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

				// プレイヤーモデルを右向きに変更
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーに時間を設定
					turnTimer_ = kTimeTurn;
				}

				if (velocity_.x < 0.0f) {

					// 逆入力中は急ブレーキ
					velocity_.x = velocity_.x * (1.0f - kAttenuation);
				}

				acceleration.x += kAcceleration;

			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {

				// プレイヤーモデルを左向きに変更
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーに時間を設定
					turnTimer_ = kTimeTurn;
				}

				if (velocity_.x > 0.0f) {

					// 逆入力中は急ブレーキ
					velocity_.x = velocity_.x * (1.0f - kAttenuation);
				}

				acceleration.x -= kAcceleration;
			}

			// 加速/減速
			velocity_ = velocity_ + acceleration;

			// 速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {
			// 非入力時は移動減衰をかける
			velocity_.x = velocity_.x * (1.0f - kAttenuation);
		}

		if (Input::GetInstance()->PushKey(DIK_UP)) {
			// ジャンプ初速
			velocity_ = velocity_ + Vector3(0, kJumpAcceleration, 0);
		}

		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態に移行
			onGround_ = false;
		}

		//==================================
		// 移動量を加味して衝突判定をする
		//==================================

		// 衝突状態を初期化
		CollisionMapInfo collisionMapInfo;

		// 移動量に速度の値をコピー
		collisionMapInfo.displacement_ = velocity_;

		// マップ衝突チェック
		MapChipCollision(collisionMapInfo);

		// 判定結果を反映して移動させる
		ReflectCollisionResult(collisionMapInfo);

		// 天井に当たっていたら処理する
		ProcessHitCeiling(collisionMapInfo);

		// 床に当たっていたら処理する
		if (collisionMapInfo.onGround_) {
			DebugText::GetInstance()->ConsolePrintf("hit ground\n");
			velocity_.y = 0.0f;
			onGround_ = true;
		}

	} else {
		// 空中状態：重力を適用しつつ、マップチップ衝突判定で床当たり判定
		velocity_ = velocity_ + Vector3(0, -kGravityAcceleration, 0);
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
		// 衝突判定
		CollisionMapInfo collisionMapInfo;
		collisionMapInfo.displacement_ = velocity_;
		MapChipCollision(collisionMapInfo);
		ReflectCollisionResult(collisionMapInfo);
		ProcessHitCeiling(collisionMapInfo);
		// 床に当たったら着地処理
		if (collisionMapInfo.onGround_) {
			DebugText::GetInstance()->ConsolePrintf("hit ground\n");
			velocity_.y = 0.0f;
			onGround_ = true;
		}

		//// 着地フラグ
		//bool landing = false;
		////==================================
		//// 接地状態の切り替え
		////==================================

		//// 落下速度
		//velocity_ = velocity_ + Vector3(0, -kGravityAcceleration, 0);

		//// 落下速度制限
		//velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

		//// 降下中？
		//if (velocity_.y < 0) {

		//	// Y座標が地面以下になったら着地
		//	if (worldTransform_.translation_.y <= 1.0f) {
		//		landing = true;
		//	}
		//}

		//if (landing) {
		//	// めり込み排斥
		//	worldTransform_.translation_.y = 1.0f;

		//	// 摩擦で横方向速度が減衰
		//	velocity_.x *= (1.0f - kAttenuation);

		//	// 下方向速度をリセット
		//	velocity_.y = 0.0f;

		//	// 接地状態に移行
		//	onGround_ = true;
		//}
	}

	//=============
	// 旋回制御
	//=============
	if (turnTimer_ > 0.0f) {

		// タイマーを1フレーム分減らす（例：1/60秒）
		turnTimer_ -= 1.0f / 60.0f;

		// 補間係数（0.0 ～ 1.0）
		float t = 1.0f - (turnTimer_ / kTimeTurn);
		t = std::clamp(t, 0.0f, 1.0f);

		// イージング関数（SmoothStep：EaseInOutの代用）
		t = t * t * (3.0f - 2.0f * t);

		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};

		// 状況に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		// 自キャラの角度を設定する
		// 線形補間で角度補間
		worldTransform_.rotation_.y = turnFirstRotationY_ + (destinationRotationY - turnFirstRotationY_) * t;
	}

	// 実際に移動
	worldTransform_.translation_ = worldTransform_.translation_ + velocity_;

	// 行列の更新
	worldTransformUtil_->WorldTransformUpdate(worldTransform_);

	//worldTransform_.TransferMatrix();
}

void Player::Draw() {

	// ここからモデルの描画
	model_->Draw(worldTransform_, *camera_);

	// DebugText::GetInstance()->ConsolePrintf("PlayerPos:%f,%f,%f\n", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
}

void Player::MapChipCollision(CollisionMapInfo& info) {

	// マップ衝突判定
	IsCollisionUp(info);
	IsCollisionBottom(info);
	IsCollisionLeft(info);
	IsCollisionRight(info);
}

void Player::IsCollisionUp(CollisionMapInfo& info) {

	if (!mapChipField_) {
		DebugText::GetInstance()->ConsolePrintf("mapChipField is null\n");
		assert(0);
		return;
	}

	// 上昇あり？
	if (info.displacement_.y <= 0.0f) {
		return;
	}

	// 移動後の4つ角の座標
	std::array<Vector3, 4> positinsNew;

	for (uint32_t i = 0; i < positinsNew.size(); ++i) {
		positinsNew[i] = CornerPosition(worldTransform_.translation_ + info.displacement_, static_cast<Corner>(i));
	}

	MapChipType mapChipType;

	bool hit = false;

	MapChipField::IndexSet indexSet;

	// 左上の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positinsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {
		hit = true;
		DebugText::GetInstance()->ConsolePrintf("hit left top ceiling block at (%d, %d)\n", indexSet.xIndex, indexSet.yIndex);
	}

	// 右上の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positinsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {
		hit = true;
		DebugText::GetInstance()->ConsolePrintf("info.isHitCeiling_ = true; disp.y = %f\n", info.displacement_.y);
	}

	// ブロックにヒット
	if (hit) {
		// めり込みを排除する方向に移動量を設定する
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positinsNew[kLeftTop]);             // 移動後の自キャラ上端座標
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex); // めり込んだブロックの範囲

		// Y移動量を求める（スライド「移動量を求める」の式に基づく）
		info.displacement_.y = std::max(0.0f, rect.bottom - ((worldTransform_.translation_.y + kHeight / 2.0f) + kBlank));

		// 天井に当たったことを記録する
		info.isHitCeiling_ = true;
	}
}

void Player::IsCollisionBottom(CollisionMapInfo& info) {
	if (!mapChipField_) {
		DebugText::GetInstance()->ConsolePrintf("mapChipField is null\n");
		assert(0);
		return;
	}
	// 下降あり？
	if (info.displacement_.y >= 0.0f) {
		return;
	}
	// 移動後の4つ角の座標
	std::array<Vector3, 4> positionsNew;
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.displacement_, static_cast<Corner>(i));
	}
	bool hit = false;
	MapChipField::IndexSet indexSet;
	MapChipType mapChipType;
	// 左下の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
		DebugText::GetInstance()->ConsolePrintf("hit left bottom block at (%d, %d)\n", indexSet.xIndex, indexSet.yIndex);
	}
	// 右下の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
		DebugText::GetInstance()->ConsolePrintf("hit right bottom block at (%d, %d)\n", indexSet.xIndex, indexSet.yIndex);
	}
	if (hit) {
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		float oldBottom = worldTransform_.translation_.y - kHeight / 2.0f;
		// スライド「移動量を求める」の式に基づく
		info.displacement_.y = std::max(info.displacement_.y, (rect.top + kBlank) - oldBottom);
		// 接地状態を記録する
		info.onGround_ = true;
	}
}

void Player::IsCollisionLeft(CollisionMapInfo& info) {
	if (!mapChipField_) {
		DebugText::GetInstance()->ConsolePrintf("mapChipField is null\n");
		assert(0);
		return;
	}
	// 左移動のみ
	if (info.displacement_.x >= 0.0f) {
		return;
	}
	// 移動後の4つ角の座標
	std::array<Vector3, kNumCorner> positionsNew;
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.displacement_, static_cast<Corner>(i));
	}
	bool hit = false;
	MapChipField::IndexSet indexSet;
	MapChipType mapChipType;
	// 左上の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
		DebugText::GetInstance()->ConsolePrintf("hit left block at (%d, %d)\n", indexSet.xIndex, indexSet.yIndex);
	}
	// 左下の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
		DebugText::GetInstance()->ConsolePrintf("hit left block at (%d, %d)\n", indexSet.xIndex, indexSet.yIndex);
	}
	if (hit) {
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		float oldLeft = worldTransform_.translation_.x - kWidth / 2.0f;
		info.displacement_.x = std::max(info.displacement_.x, (rect.right + kBlank) - oldLeft);
		info.isHitWall_ = true;
	}
}

void Player::IsCollisionRight(CollisionMapInfo& info) {
	if (!mapChipField_) {
		assert(0);
		return;
	}
	// 右移動のみ
	if (info.displacement_.x <= 0.0f) {
		return;
	}
	// 移動後の4つ角の座標
	std::array<Vector3, kNumCorner> positionsNew;
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.displacement_, static_cast<Corner>(i));
	}
	bool hit = false;
	MapChipField::IndexSet indexSet;
	MapChipType mapChipType;
	// 右上の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
		DebugText::GetInstance()->ConsolePrintf("hit right block at (%d, %d)\n", indexSet.xIndex, indexSet.yIndex);
	}
	// 右下の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
		DebugText::GetInstance()->ConsolePrintf("hit right block at (%d, %d)\n", indexSet.xIndex, indexSet.yIndex);
	}
	if (hit) {
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		float oldRight = worldTransform_.translation_.x + kWidth / 2.0f;
		info.displacement_.x = std::min(info.displacement_.x, (rect.left - kBlank) - oldRight);
		info.isHitWall_ = true;
	}
}

void Player::OnCollision(const Enemy* enemy) {

	// 無意味な処理を入れておく
	(void)enemy;

	// ジャンプ
	DebugText::GetInstance()->ConsolePrintf("PlayerIsHitEnemy\n");
	isDead_ = true;
	//velocity_ = velocity_ + Vector3(0.0f, 0.05f, 0.0f);
}

AABB Player::GetAABB() { 
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

// ③判定結果を反映して移動させる
void Player::ReflectCollisionResult(const CollisionMapInfo& info) {
	// 移動
	worldTransform_.translation_ = worldTransform_.translation_ + info.displacement_;
}

// ④天井に接触している場合の処理
void Player::ProcessHitCeiling(const CollisionMapInfo& info) {
	// 天井に当たった？
	if (info.isHitCeiling_) {
		DebugText::GetInstance()->ConsolePrintf("hit ceiling\n");
		velocity_.y = 0;
	}
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {

	Vector3 offsetTable[kNumCorner] = {
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0.0f}, // 左上
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0.0f}, // 左下
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0.0f}, // 右上
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0.0f}  // 右下
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}

Player::~Player() { delete worldTransformUtil_; }