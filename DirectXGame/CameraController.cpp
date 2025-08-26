#include "CameraController.h"
#include <cassert>

void CameraController::Initialize(Camera* camera) { 

	camera_ = camera;

	camera_->Initialize();
}

void CameraController::Update() {

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->worldTransform_;

	// 追従対象とオフセットからカメラの目標座標を計算
	targetPosition_ = targetWorldTransform.translation_ + targetOffset_ + target_->GetVelocity() * kVelocityBias;

	// 座標補間（カメラ座標 → 目標座標）
	camera_->translation_ = Lerp(camera_->translation_, targetPosition_, kInterpolationRate);

	// 範囲制限処理（追従対象が画面外に出ないようマージンを加味）
	camera_->translation_.x = max(camera_->translation_.x, targetPosition_.x + kMargin.left);
	camera_->translation_.x = min(camera_->translation_.x, targetPosition_.x + kMargin.right);

	camera_->translation_.y = max(camera_->translation_.y, targetPosition_.y + kMargin.bottom);
	camera_->translation_.y = min(camera_->translation_.y, targetPosition_.y + kMargin.top);

	// 範囲制限処理（移動範囲を超えないよう clamp）
	camera_->translation_.x = std::clamp(camera_->translation_.x, movableArea_.left, movableArea_.right);
	camera_->translation_.y = std::clamp(camera_->translation_.y, movableArea_.bottom, movableArea_.top);

	// 行列の更新
	camera_->UpdateMatrix();

}

void CameraController::Reset() {

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->worldTransform_;

	// 追従対象とオフセットからカメラの座標を計算
	camera_->translation_ = targetWorldTransform.translation_ + targetOffset_;

}