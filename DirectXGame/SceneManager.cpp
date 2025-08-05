#include "SceneManager.h"

// シーンを格納する場所を空の状態で生成
BaseScene* SceneManager::nowScene_ = nullptr;

void SceneManager::ChangeScene(Scene scene) {

	nowScene_ = nullptr;
	delete nowScene_;

	switch (scene) {
	case SceneManager::TITLE:
		nowScene_ = new TitleScene;
		nowScene_->Initialize();

		break;
	case SceneManager::GAME:
		nowScene_ = new GamePlayScene;
		nowScene_->Initialize();

		break;
	default:
		break;
	}
}

void SceneManager::Update() { 
	nowScene_->Update();
}

void SceneManager::Draw() { 
	nowScene_->Draw();
}
