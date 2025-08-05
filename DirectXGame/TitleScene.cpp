#include "TitleScene.h"

void TitleScene::Initialize() {
	
	playerModel_ = Model::CreateFromOBJ("player", true);
	camera_ = new Camera;
	camera_->farZ = 1500.0f; // なんかここいじっても変わんないからCamera.hいじってる
	camera_->Initialize();

	player_ = new Player;
	Vector3 playerPosition = {0.0f, 0.0f, 0.0f};
	player_->Initialize(playerModel_, camera_, playerPosition);

}

void TitleScene::Update() { 
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		SceneManager::ChangeScene(SceneManager::GAME);
		//finished_ = true;
	}
}

void TitleScene::Draw() {

	// 3Dモデル描画前処理
	Model::PreDraw();

	player_->Draw();

	// 3Dモデル描画後処理
	Model::PostDraw();

}
