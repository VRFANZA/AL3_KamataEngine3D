#include "Enemy.h"

void Enemy::Initialize(Model* model, Camera* camera, const Vector3& position) {
	// NULLチェック
	assert(model);
	assert(camera);
	model_ = model;
	camera_ = camera;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	// 速度を設定
	velocity_ = {-kWalkSpeed, 0.0f, 0.0f};

	// ワールドトランスフォーム更新クラスの生成
	worldTransformUtil_ = new WorldTransformUtil();

	walkTimer_ = 0.0f;
}

void Enemy::Update() {

	// タイマーを加算
	walkTimer_ = walkTimer_ + 1.0f / 60.0f;

	// 回転アニメーション
	//float param = std::sinf((2.0f * static_cast<float>(M_PI)) * walkTimer_ / kWalkMotionTime);
	//float degree = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.z = worldTransform_.rotation_.z * (180.0f / static_cast<float>(M_PI));

	worldTransform_.rotation_.z = std::sinf((2.0f * static_cast<float>(M_PI)) * walkTimer_ / kWalkMotionTime);

	// 移動
	worldTransform_.translation_ = worldTransform_.translation_ + velocity_;

	// 行列の更新
	worldTransformUtil_->WorldTransformUpdate(worldTransform_);
}

void Enemy::Draw() {

	// モデルの描画
	model_->Draw(worldTransform_, *camera_);
}

void Enemy::OnCollision(const Player* player) {

	// 無意味な処理を入れておく
	(void)player;
}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}
