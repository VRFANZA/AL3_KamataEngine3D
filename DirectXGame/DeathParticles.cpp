#include "DeathParticles.h"

void DeathParticles::Initialize(Model* model, Camera* camera, const Vector3& position) {
	// NULLチェック
	assert(model);
	assert(camera);

	model_ = model;
	camera_ = camera;

	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};

	// ワールドトランスフォーム更新クラスの生成
	worldTransformUtil_ = new WorldTransformUtil();

	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
}

void DeathParticles::Update() {

	if (isFinished_) {
		return;
	}

	// パーティクルの移動処理
	for (uint32_t i = 0; i < kNumberOfParticles; ++i) {

		// 基本となる速度ベクトル
		Vector3 velocity = {kSpeed, 0, 0};

		// 回転角を計算
		float angle = kAngleUnit * i;

		// z軸回りの回転行列
		Matrix4x4 rotationMatrix = MakeRotationMatrixZ(angle);

		// 基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, rotationMatrix);

		// 移動処理
		worldTransforms_[i].translation_ = worldTransforms_[i].translation_ + velocity;

	}

	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		isFinished_ = true;
	}

	// アルファ値を時間経過に応じて減衰
	color_.w = std::clamp(1.0f - (counter_ / kDuration), 0.0f, 1.0f);
	objectColor_.SetColor(color_);

	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransformUtil_->WorldTransformUpdate(worldTransform);
	}
}

void DeathParticles::Draw() {
	if (isFinished_) {
		return;
	}

	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *camera_, &objectColor_);
		
	}
}

Vector3 DeathParticles::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 resultVector3;

	resultVector3.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	resultVector3.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	resultVector3.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);

	resultVector3.x /= w;
	resultVector3.y /= w;
	resultVector3.z /= w;

	return resultVector3;
}
