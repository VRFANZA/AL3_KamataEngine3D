#include "GamePlayScene.h"

void GamePlayScene::Initialize() {
	// ここにインゲームの初期化処理を書く

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// スプライトのインスタンスを生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// 3Dモデルの生成
	model_ = Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// カメラの初期化
	camera_ = new Camera;
	camera_->Initialize();

	// プレイヤーの生成
	player_ = new Player();

	// プレイヤーの初期化
	player_->Initialize(model_,textureHandle_,camera_);
}

void GamePlayScene::Update() {
	// ここにインゲームの更新処理を書く

	// プレイヤーの更新処理
	player_->Update();
}

void GamePlayScene::Draw() {
	// ここにインゲームの描画処理を書く
	// プレイヤーの描画処理
	player_->Draw();

	// スプライト描画前処理
	Sprite::PreDraw();

	// ここからスプライトの描画

	// スプライト描画後処理
	Sprite::PostDraw();

	// 3Dモデル描画前処理
	Model::PreDraw();

	// ここからモデルの描画

	// 3Dモデル描画後処理
	Model::PostDraw();
}

GamePlayScene::~GamePlayScene() {
	// ここに解放処理とか書く
	// インスタンスの持ち主のみが解放
	delete player_;
	delete model_;
	delete sprite_;
	delete camera_;
}
