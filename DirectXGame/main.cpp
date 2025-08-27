#include <Windows.h>
#include <KamataEngine.h>
#include "SceneManager.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	// エンジンの初期化
	Initialize(L"LE2B_16_タカムラ_シュン_AL3");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// シーンのインスタンスの生成
	SceneManager* sceneManager = new SceneManager();

	// 最初のシーンを設定
	sceneManager->ChangeScene(SceneManager::TITLE);

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// 更新処理
		sceneManager->Update();
		

		// 描画開始
		dxCommon->PreDraw();

		// 描画処理
		sceneManager->Draw();

		// 描画終了
		dxCommon->PostDraw();

	}

	delete sceneManager;

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}
