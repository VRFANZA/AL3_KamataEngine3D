#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle,Camera* camera) {
	// NULLチェック
	assert(model);
	assert(camera);

	// 引数として受け取ったデータをメンバ変数にコピー
	model_ = model;
	textereHandle_ = textureHandle;
	camera_ = camera;

	// ワールドトランスフォーム更新クラスの生成
	worldTransformUtil_ = new WorldTransformUtil();

	worldTransform_.Initialize();
}

void Player::Update() {

	worldTransformUtil_->WorldTransformUpdate(worldTransform_);

}

void Player::Draw() {

	// ここからモデルの描画
	model_->Draw(worldTransform_, *camera_, textereHandle_);

}

Player::~Player() { 
	delete worldTransformUtil_;
}
