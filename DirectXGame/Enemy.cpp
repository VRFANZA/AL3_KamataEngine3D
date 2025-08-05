#include "Enemy.h"

void Enemy::Initialize(Model* model,Camera* camera, const Vector3& position) {
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
}

void Enemy::Update() {

	// 移動
	worldTransform_.translation_ = worldTransform_.translation_ + velocity_;

	// 行列の更新
	worldTransformUtil_->WorldTransformUpdate(worldTransform_);
}

void Enemy::Draw() {

	// モデルの描画
	model_->Draw(worldTransform_, *camera_);
}