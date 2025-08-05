#include "DeathParticles.h"

void DeathParticles::Initialize(Model* model, Camera* camera, const Vector3& position) {
	// NULLチェック
	assert(model);
	assert(camera);

	model_ = model;
	camera_ = camera;

	// ワールドトランスフォーム更新クラスの生成
	worldTransformUtil_ = new WorldTransformUtil();

	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
}

void DeathParticles::Update() {
	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransformUtil_->WorldTransformUpdate(worldTransform);
	}
}

void DeathParticles::Draw() {
	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *camera_);
	}
}
