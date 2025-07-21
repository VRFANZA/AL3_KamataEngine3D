#include "Skydome.h"

void Skydome::Initialize(Model* model, Camera* camera) {
	
	worldTransform_.Initialize();

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	modelSkydome_ = model;
	cameraSkydome_ = camera;

}

void Skydome::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Skydome::Draw() {

	assert(cameraSkydome_ && "キャメラぬるぽ");

	// ここからモデルの描画
	modelSkydome_->Draw(worldTransform_, *cameraSkydome_);

}

Skydome::~Skydome() { 

}
