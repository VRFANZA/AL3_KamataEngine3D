#include "Fade.h"

void Fade::Start(Status status, float duration) {

	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;

}

void Fade::Stop() {

	status_ = Status::None;

}

bool Fade::IsFinished() const { 

	// フェードによる分岐
	switch (status_) {
	case Fade::Status::FadeIn:

		if (counter_ >= duration_) {
			return true;
		} else {
			return false;
		}

		break;
	case Fade::Status::FadeOut:

		if (counter_ >= duration_) {
			return true;
		} else {
			return false;
		}

		break;
	default:

		return true;

		break;
	}

}

void Fade::Initialize() {

	sprite_ = sprite_->Create(fadeTexture, position_, color_, anchorpoint_, isFlipX_, isFlipY_);
	sprite_->SetSize(size_);
	sprite_->SetColor(color_);

}

void Fade::Update() {

	switch (status_) {
	case Fade::Status::None:

		// 何もしない

		break;
	case Fade::Status::FadeIn:

		// フェードインの処理
		// 1フレーム分の秒数をカウントアップ
		counter_ += 1.0f / 60.0f;

		// フェード効果時間に達したら停止
		// counter_ = std::min(counter_, duration_);

		if (counter_ >= duration_) {
			counter_ = duration_;
		}

		// 0.0fから1.0fの間で経過時間がフェード効果時間に近づくほどα値を小さくする
		sprite_->SetColor(Vector4(0, 0, 0, 1.0f - std::clamp(counter_ / duration_, 0.0f, 1.0f)));

		break;
	case Fade::Status::FadeOut:

		// フェードアウトの処理
		// 1フレーム分の秒数をカウントアップ
		counter_ += 1.0f / 60.0f;

		// フェード効果時間に達したら停止
		//counter_ = std::min(counter_, duration_);

		if (counter_ >= duration_) {
			counter_ = duration_;
		}

		// 0.0fから1.0fの間で経過時間がフェード効果時間に近づくほどα値を大きくする
		sprite_->SetColor(Vector4(0, 0, 0, std::clamp(counter_ / duration_, 0.0f, 1.0f)));

		break;
	default:
		break;
	}

}

void Fade::Draw() {

	if (status_ == Status::None) {
		return;
	}

	Sprite::PreDraw();
	sprite_->Draw();
	Sprite::PostDraw();

}
