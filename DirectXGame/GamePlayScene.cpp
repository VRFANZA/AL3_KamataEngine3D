#include "GamePlayScene.h"

void GamePlayScene::Initialize() {
	//=================================
	// ここにインゲームの初期化処理を書く
	//=================================

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// サウンドデータを読み込む
	soundDataHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");

	// スプライトを生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// 音声再生 第二引数にtrueを入れればループ再生可
	Audio::GetInstance()->PlayWave(soundDataHandle_ /*,true*/);

	// モデルを生成
	model_ = Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// カメラの初期化
	camera_.Initialize();

	// デバッグカメラの生成
	debugcamela_ = new DebugCamera(1280, 720);
	
	// ライン描画が参照するカメラを指定する(参照渡し)
	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	// 軸方向表示の表示を有効化
	AxisIndicator::GetInstance()->SetVisible(true);

	// 軸方向表示が参照するビュープロジェクションを指定する(参照渡し)
	AxisIndicator::GetInstance()->SetTargetCamera(&debugcamela_->GetCamera());
}

void GamePlayScene::Update() {
	//==============================
	// ここにインゲームの更新処理を書く
	//==============================
#ifdef _DEBUG

	// デバックテキストの表示
	ImGui::Text("Kamata Tarou %d.%d.%d", 2025, 06, 30);

	// 入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);

	// スライダー
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);

#endif //_DEBUG

	// SPACEキーを押す
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {

		// 音声停止
		Audio::GetInstance()->StopWave(soundDataHandle_);
	}

	// スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();

	// 座標を{2,1}移動
	position.x += 2.0f;
	position.y += 1.0f;

	// 移動下座標をスプライトに反映
	sprite_->SetPosition(position);
}

void GamePlayScene::Draw() {
	//===============================
	// ここにインゲームの描画処理を書く
	//===============================

	// スプライト描画前処理
	Sprite::PreDraw();

	// モデル描画前処理
	Model::PreDraw();

	// ここにスプライトインスタンスの描画処理を記述
	//sprite_->Draw();

	// ラインを描画する (始点座標,終点座標,RGBA)
	//PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

	// ここに3Dモデルインスタンスの描画処理を記述
	model_->Draw(worldTransform_, debugcamela_->GetCamera(), textureHandle_);

	#ifdef _DEBUG

	// 軸方向の描画
	AxisIndicator::GetInstance()->Draw();

#endif // _DEBUG


	// モデル描画前処理
	Model::PostDraw();

	// スプライト描画後処理
	Sprite::PostDraw();

	// デバッグカメラの更新
	debugcamela_->Update();
}

GamePlayScene::~GamePlayScene() {
	//===============================
	// ここにデストラクタの処理を書く
	//===============================

	delete sprite_;
	delete model_;
	delete debugcamela_;
}

