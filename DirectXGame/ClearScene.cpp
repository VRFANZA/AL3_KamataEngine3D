#include "ClearScene.h"

void ClearScene::Initialize() {

	playerModel_ = Model::CreateFromOBJ("player", true);
	camera_ = new Camera;
	camera_->farZ = 1500.0f; // なんかここいじっても変わんないからCamera.hいじってる
	camera_->Initialize();

	player_ = new Player;
	Vector3 playerPosition = {0.0f, 0.0f, 0.0f};
	player_->Initialize(playerModel_, camera_, playerPosition);

	fade_ = new Fade;
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void ClearScene::Update() {
	switch (phase_) {
	case ClearScene::Phase::kFadeIn:

		if (fade_->IsFinished()) {
			fade_->Stop();
			phase_ = Phase::kMain;
		}

		break;
	case ClearScene::Phase::kMain:

		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			phase_ = Phase::kFadeOut;
			// finished_ = true;
		}

		break;
	case ClearScene::Phase::kFadeOut:

		if (fade_->IsFinished()) {
			SceneManager::ChangeScene(SceneManager::TITLE);
		}

		break;
	default:
		break;
	}

	fade_->Update();
}

void ClearScene::Draw() {
	// 3Dモデル描画前処理
	Model::PreDraw();

	player_->Draw();

	// 3Dモデル描画後処理
	Model::PostDraw();

	fade_->Draw();
}
