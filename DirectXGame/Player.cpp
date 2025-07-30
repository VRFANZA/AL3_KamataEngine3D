#define NOMINMAX
#include "Player.h"

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }

Vector3 Player::Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

void Player::Initialize(Model* model, Camera* camera, const Vector3& position) {
	// NULLチェック
	assert(model);
	assert(camera);

	// ワールドトランスフォーム更新クラスの生成
	worldTransformUtil_ = new WorldTransformUtil();

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// モデルをy軸回りにπ/2(90°)回転
	//worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	model_ = model;
	camera_ = camera;
}

void Player::Update() {

	//=============
	// 移動入力
	//=============
	// 接地確認
	if (onGround_) {

		// 接地時のみ左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

				// プレイヤーモデルを右向きに変更
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
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

	} else {
		// 落下速度
		velocity_ = velocity_ + Vector3(0, -kGravityAcceleration, 0);

		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

		// 着地フラグ
		bool landing = false;

		// 降下中？
		if (velocity_.y < 0) {

			// Y座標が地面以下になったら着地
			if (worldTransform_.translation_.y <= 1.0f) {
				landing = true;
			}
		}

		if (landing) {
			// めり込み排斥
			worldTransform_.translation_.y = 1.0f;

			// 摩擦で横方向速度が減衰
			velocity_.x *= (1.0f - kAttenuation);

			// 下方向速度をリセット
			velocity_.y = 0.0f;

			// 接地状態に移行
			onGround_ = true;
		}
	}

	// 旋回制御
	// スコープ内で処理
	//{
	//	// 左右の自キャラ角度テーブル
	//	float destinationRotationYTable[] = {
	//		std::numbers::pi_v<float> / 2.0f,
	//		std::numbers::pi_v<float> * 3.0f / 2.0f
	//	};

	//	// 状況に応じた角度を取得する
	//	float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

	//	// 自キャラの角度を設定する
	//	worldTransform_.rotation_.y = destinationRotationY;
	//}

	// 移動
	worldTransform_.translation_ = worldTransform_.translation_ + velocity_;

	// 行列の更新
	worldTransformUtil_->WorldTransformUpdate(worldTransform_);
}

void Player::Draw() {

	// ここからモデルの描画
	model_->Draw(worldTransform_, *camera_);
}

Player::~Player() { delete worldTransformUtil_; }
