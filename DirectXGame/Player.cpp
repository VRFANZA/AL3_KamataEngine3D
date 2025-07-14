#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle,Camera* camera) {
	// NULLチェック
	assert(model);
	assert(camera);

	// 引数として受け取ったデータをメンバ変数にコピー
	model_ = model;
	textereHandle_ = textureHandle;
	camera_ = camera;

	worldTransform_.Initialize();
}

void Player::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw() {

	// ここからモデルの描画
	model_->Draw(worldTransform_, *camera_, textereHandle_);

}

Player::~Player() {

}
