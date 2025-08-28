#include "TitleScene.h"

void TitleScene::Initialize() {
	
	// テクスチャの読み込み
	// ここ書き換える=================================================
	textureHandle_ = TextureManager::Load("Title.png");

	// スプライトのインスタンスを生成
	sprite_ = Sprite::Create(textureHandle_, {0, 0});

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

void TitleScene::Update() { 

	switch (phase_) {
	case TitleScene::Phase::kFadeIn:

		if (fade_->IsFinished()) {
			fade_->Stop();
			phase_ = Phase::kMain;
		}

		break;
	case TitleScene::Phase::kMain:

		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			phase_ = Phase::kFadeOut;
			// finished_ = true;
		}

		break;
	case TitleScene::Phase::kFadeOut:

		if (fade_->IsFinished()) {
			SceneManager::ChangeScene(SceneManager::GAME);
		}

		break;
	default:
		break;
	}

	

	fade_->Update();

}

void TitleScene::Draw() {

	// スプライト描画前処理
	Sprite::PreDraw();

	// ここからスプライトの描画
	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

	// 3Dモデル描画前処理
	Model::PreDraw();

	player_->Draw();

	// 3Dモデル描画後処理
	Model::PostDraw();

	fade_->Draw();

}

TitleScene::~TitleScene() {

	delete sprite_;
	delete fade_;

}
