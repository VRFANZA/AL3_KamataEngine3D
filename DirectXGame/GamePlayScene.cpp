#include "GamePlayScene.h"

Matrix4x4 GamePlayScene::Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2) {
	Matrix4x4 resoultMatrix4x4;

	resoultMatrix4x4.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0] + matrix1.m[0][3] * matrix2.m[3][0];
	resoultMatrix4x4.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1] + matrix1.m[0][3] * matrix2.m[3][1];
	resoultMatrix4x4.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2] + matrix1.m[0][3] * matrix2.m[3][2];
	resoultMatrix4x4.m[0][3] = matrix1.m[0][0] * matrix2.m[0][3] + matrix1.m[0][1] * matrix2.m[1][3] + matrix1.m[0][2] * matrix2.m[2][3] + matrix1.m[0][3] * matrix2.m[3][3];

	resoultMatrix4x4.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0] + matrix1.m[1][3] * matrix2.m[3][0];
	resoultMatrix4x4.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1] + matrix1.m[1][3] * matrix2.m[3][1];
	resoultMatrix4x4.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2] + matrix1.m[1][3] * matrix2.m[3][2];
	resoultMatrix4x4.m[1][3] = matrix1.m[1][0] * matrix2.m[0][3] + matrix1.m[1][1] * matrix2.m[1][3] + matrix1.m[1][2] * matrix2.m[2][3] + matrix1.m[1][3] * matrix2.m[3][3];

	resoultMatrix4x4.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0] + matrix1.m[2][3] * matrix2.m[3][0];
	resoultMatrix4x4.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1] + matrix1.m[2][3] * matrix2.m[3][1];
	resoultMatrix4x4.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2] + matrix1.m[2][3] * matrix2.m[3][2];
	resoultMatrix4x4.m[2][3] = matrix1.m[2][0] * matrix2.m[0][3] + matrix1.m[2][1] * matrix2.m[1][3] + matrix1.m[2][2] * matrix2.m[2][3] + matrix1.m[2][3] * matrix2.m[3][3];

	resoultMatrix4x4.m[3][0] = matrix1.m[3][0] * matrix2.m[0][0] + matrix1.m[3][1] * matrix2.m[1][0] + matrix1.m[3][2] * matrix2.m[2][0] + matrix1.m[3][3] * matrix2.m[3][0];
	resoultMatrix4x4.m[3][1] = matrix1.m[3][0] * matrix2.m[0][1] + matrix1.m[3][1] * matrix2.m[1][1] + matrix1.m[3][2] * matrix2.m[2][1] + matrix1.m[3][3] * matrix2.m[3][1];
	resoultMatrix4x4.m[3][2] = matrix1.m[3][0] * matrix2.m[0][2] + matrix1.m[3][1] * matrix2.m[1][2] + matrix1.m[3][2] * matrix2.m[2][2] + matrix1.m[3][3] * matrix2.m[3][2];
	resoultMatrix4x4.m[3][3] = matrix1.m[3][0] * matrix2.m[0][3] + matrix1.m[3][1] * matrix2.m[1][3] + matrix1.m[3][2] * matrix2.m[2][3] + matrix1.m[3][3] * matrix2.m[3][3];

	return resoultMatrix4x4;
}

Matrix4x4 GamePlayScene::MakeAffineMatrix(Vector3& scale, Vector3& rotate, Vector3& translate) {
	//====================
	// 拡縮の行列の作成
	//====================
	Matrix4x4 scaleMatrix4x4;
	scaleMatrix4x4.m[0][0] = scale.x;
	scaleMatrix4x4.m[0][1] = 0.0f;
	scaleMatrix4x4.m[0][2] = 0.0f;
	scaleMatrix4x4.m[0][3] = 0.0f;

	scaleMatrix4x4.m[1][0] = 0.0f;
	scaleMatrix4x4.m[1][1] = scale.y;
	scaleMatrix4x4.m[1][2] = 0.0f;
	scaleMatrix4x4.m[1][3] = 0.0f;

	scaleMatrix4x4.m[2][0] = 0.0f;
	scaleMatrix4x4.m[2][1] = 0.0f;
	scaleMatrix4x4.m[2][2] = scale.z;
	scaleMatrix4x4.m[2][3] = 0.0f;

	scaleMatrix4x4.m[3][0] = 0.0f;
	scaleMatrix4x4.m[3][1] = 0.0f;
	scaleMatrix4x4.m[3][2] = 0.0f;
	scaleMatrix4x4.m[3][3] = 1.0f;

	//===================
	// 回転の行列の作成
	//===================
	// Xの回転行列
	Matrix4x4 rotateMatrixX;
	rotateMatrixX.m[0][0] = 1.0f;
	rotateMatrixX.m[0][1] = 0.0f;
	rotateMatrixX.m[0][2] = 0.0f;
	rotateMatrixX.m[0][3] = 0.0f;

	rotateMatrixX.m[1][0] = 0.0f;
	rotateMatrixX.m[1][1] = cosf(rotate.x);
	rotateMatrixX.m[1][2] = sinf(rotate.x);
	rotateMatrixX.m[1][3] = 0.0f;

	rotateMatrixX.m[2][0] = 0.0f;
	rotateMatrixX.m[2][1] = -sinf(rotate.x);
	rotateMatrixX.m[2][2] = cosf(rotate.x);
	rotateMatrixX.m[2][3] = 0.0f;

	rotateMatrixX.m[3][0] = 0.0f;
	rotateMatrixX.m[3][1] = 0.0f;
	rotateMatrixX.m[3][2] = 0.0f;
	rotateMatrixX.m[3][3] = 1.0f;

	// Yの回転行列
	Matrix4x4 rotateMatrixY;
	rotateMatrixY.m[0][0] = cosf(rotate.y);
	rotateMatrixY.m[0][1] = 0.0f;
	rotateMatrixY.m[0][2] = -sinf(rotate.y);
	rotateMatrixY.m[0][3] = 0.0f;

	rotateMatrixY.m[1][0] = 0.0f;
	rotateMatrixY.m[1][1] = 1.0f;
	rotateMatrixY.m[1][2] = 0.0f;
	rotateMatrixY.m[1][3] = 0.0f;

	rotateMatrixY.m[2][0] = sinf(rotate.y);
	rotateMatrixY.m[2][1] = 0.0f;
	rotateMatrixY.m[2][2] = cosf(rotate.y);
	rotateMatrixY.m[2][3] = 0.0f;

	rotateMatrixY.m[3][0] = 0.0f;
	rotateMatrixY.m[3][1] = 0.0f;
	rotateMatrixY.m[3][2] = 0.0f;
	rotateMatrixY.m[3][3] = 1.0f;

	// Zの回転行列
	Matrix4x4 rotateMatrixZ;
	rotateMatrixZ.m[0][0] = cosf(rotate.z);
	rotateMatrixZ.m[0][1] = sinf(rotate.z);
	rotateMatrixZ.m[0][2] = 0.0f;
	rotateMatrixZ.m[0][3] = 0.0f;

	rotateMatrixZ.m[1][0] = -sinf(rotate.z);
	rotateMatrixZ.m[1][1] = cosf(rotate.z);
	rotateMatrixZ.m[1][2] = 0.0f;
	rotateMatrixZ.m[1][3] = 0.0f;

	rotateMatrixZ.m[2][0] = 0.0f;
	rotateMatrixZ.m[2][1] = 0.0f;
	rotateMatrixZ.m[2][2] = 1.0f;
	rotateMatrixZ.m[2][3] = 0.0f;

	rotateMatrixZ.m[3][0] = 0.0f;
	rotateMatrixZ.m[3][1] = 0.0f;
	rotateMatrixZ.m[3][2] = 0.0f;
	rotateMatrixZ.m[3][3] = 1.0f;

	// 回転行列の作成
	Matrix4x4 rotateMatrix4x4;

	rotateMatrix4x4 = Multiply(rotateMatrixX, Multiply(rotateMatrixY, rotateMatrixZ));

	//==================
	// 移動の行列の作成
	//==================
	Matrix4x4 translateMatrix4x4;
	translateMatrix4x4.m[0][0] = 1.0f;
	translateMatrix4x4.m[0][1] = 0.0f;
	translateMatrix4x4.m[0][2] = 0.0f;
	translateMatrix4x4.m[0][3] = 0.0f;

	translateMatrix4x4.m[1][0] = 0.0f;
	translateMatrix4x4.m[1][1] = 1.0f;
	translateMatrix4x4.m[1][2] = 0.0f;
	translateMatrix4x4.m[1][3] = 0.0f;

	translateMatrix4x4.m[2][0] = 0.0f;
	translateMatrix4x4.m[2][1] = 0.0f;
	translateMatrix4x4.m[2][2] = 1.0f;
	translateMatrix4x4.m[2][3] = 0.0f;

	translateMatrix4x4.m[3][0] = translate.x;
	translateMatrix4x4.m[3][1] = translate.y;
	translateMatrix4x4.m[3][2] = translate.z;
	translateMatrix4x4.m[3][3] = 1.0f;

	//====================
	// アフィン行列の作成
	//====================
	// 上で作った行列からアフィン行列を作る
	Matrix4x4 affineMatrix4x4;

	affineMatrix4x4 = Multiply(translateMatrix4x4, Multiply(rotateMatrix4x4, scaleMatrix4x4));

	return affineMatrix4x4;
}

void GamePlayScene::Initialize() {
	// ここにインゲームの初期化処理を書く

	// テクスチャの読み込み
	// textureHandle_ = TextureManager::Load("uvChecker.png");

	// スプライトのインスタンスを生成
	// sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// ゲームプレイフェーズから開始
	phase_ = Phase::kFadeIn;

	// 3Dモデルの生成
	playerModel_ = Model::CreateFromOBJ("player", true);
	enemyModel_ = Model::CreateFromOBJ("Enemy", true);
	blockModel_ = Model::CreateFromOBJ("Block", true);
	throughBlockModel_ = Model::CreateFromOBJ("ThroughBlock", true);
	deathFloor_ = Model::CreateFromOBJ("DeathFloor", true);
	goalModel_ = Model::CreateFromOBJ("Goal", true);
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// カメラの初期化
	camera_ = new Camera;
	camera_->farZ = 1500.0f; // なんかここいじっても変わんないからCamera.hいじってる
	camera_->Initialize();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// マップチップの生成
	mapChipField_ = new MapChipField;

	// マップチップのcsvファイルをロード
	// mapChipField_->LoadMapChipCsv("Resources/AL3_02_04_mapchip.csv");
	mapChipField_->LoadMapChipCsv("Resources/AL3_Assessment_mapchip.csv");

	// マップチップを実際に生成
	GenerateBlocks();

	// プレイヤーの生成
	player_ = new Player();

	// プレイヤーの初期位置をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);

	// プレイヤーの初期化
	player_->Initialize(playerModel_, camera_, playerPosition);

	// player_->SetMapChipField(mapChipField_);

	// マップチップデータをセット
	player_->SetMapChipField(mapChipField_);

	deathParticles_ = new DeathParticles;
	deathParticles_->Initialize(playerModel_, camera_, playerPosition);

	// 敵の生成

	for (uint32_t i = 0; i < kNumberOfEnemies; ++i) {
		Enemy* newEnemy = new Enemy();

		// 敵の初期位置をマップチップ番号で指定
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(15 + (i * 2), 18 - i);
		newEnemy->Initialize(enemyModel_, camera_, enemyPosition);

		enemies_.push_back(newEnemy);
	}

	// 敵の初期位置をマップチップ番号で指定
	// Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(10, 18);

	// 敵の初期化
	// enemy_->Initialize(enemyModel_, camera_, enemyPosition);

	// 天球の生成
	skydome_ = new Skydome();

	// 天球の初期化
	skydome_->Initialize(modelSkydome_, camera_);

	// ワールドトランスフォーム更新クラスの生成
	worldTransformUtil_ = new WorldTransformUtil();

	// カメラの生成
	cameraController_ = new CameraController();

	// 初期化
	cameraController_->Initialize(camera_);

	// 追従対象をセット
	cameraController_->SetTarget(player_);

	// リセット
	cameraController_->Reset();

	// フェードの生成
	fade_ = new Fade;
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 3.0f);
}

void GamePlayScene::Update() {
	// ここにインゲームの更新処理を書く

	ChangePhase();
	fade_->Update();
}

void GamePlayScene::Draw() {
	// ここにインゲームの描画処理を書く

	// スプライト描画前処理
	Sprite::PreDraw();

	// ここからスプライトの描画

	// スプライト描画後処理
	Sprite::PostDraw();

	// 3Dモデル描画前処理
	Model::PreDraw();

	// プレイヤーの描画処理
	if (phase_ == Phase::kPlay) {
		player_->Draw();
	}

	// パーティクルの描画
	if (phase_ == Phase::kDeath) {
		if (isDeathParticlesIsExist_) {
			deathParticles_->Draw();
		}
	}

	// 敵の描画
	for (auto& newEnemy : enemies_) {
		newEnemy->Draw();
	}
	// enemy_->Draw();

	// 天球の描画
	skydome_->Draw();

	//// ここからモデルの描画
	//// ブロックの描画
	// for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
	//	for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
	//		if (!worldTransformBlock)
	//			continue;

	//		blockModel_->Draw(*worldTransformBlock, *camera_);
	//		throughBlockModel_->Draw(*worldTransformBlock, *camera_);
	//	}
	//}

	// ここからモデルの描画
	// ブロックの描画（マップチップ種別ごとにモデルを描き分け）
	for (uint32_t i = 0; i < worldTransformBlocks_.size(); ++i) {
		for (uint32_t j = 0; j < worldTransformBlocks_[i].size(); ++j) {
			WorldTransform* wt = worldTransformBlocks_[i][j];
			if (!wt) {
				continue;
			}

			MapChipType type = mapChipField_->GetMapChipTypeByIndex(j, i);

			switch (type) {
			case MapChipType::kBlock:
				if (blockModel_) {
					blockModel_->Draw(*wt, *camera_);
				}
				break;
			case MapChipType::kThroughBlock:
				if (throughBlockModel_) {
					throughBlockModel_->Draw(*wt, *camera_);
				}
				break;
			case MapChipType::kDeathFloor:
				// 専用モデルが無ければ暫定で通常ブロックを使用
				if (deathFloor_) {
					deathFloor_->Draw(*wt, *camera_);
				}
				break;
			case MapChipType::kGoal:
				// 専用モデルが無ければ暫定で通常ブロックを使用
				if (goalModel_) {
					goalModel_->Draw(*wt, *camera_);
				}
				break;
			default: // kBlank, kGoal 等は描画しない or 専用モデルがあれば分岐を追加
				break;
			}
		}
	}

	// 3Dモデル描画後処理
	Model::PostDraw();

	// フェードの描画
	fade_->Draw();
}

void GamePlayScene::GenerateBlocks() {
	//============
	// ブロック
	//============
	// 要素数
	const uint32_t kNumBlockVirtical = mapChipField_->GetNumBlockVirtical();
	const uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更する
	// 列数を設定
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {

		// 1列の要素数を設定
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);

		// ブロックの生成
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock
				|| mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kThroughBlock 
				|| mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kDeathFloor 
				|| mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kGoal) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

void GamePlayScene::CheckAllCollisions() {

#pragma region

	{
		// 判定対象1と2の座標
		AABB aabb1, aabb2;

		// 自キャラの座標
		aabb1 = player_->GetAABB();

		// 自キャラと全ての敵との当たり判定
		for (Enemy* enemy : enemies_) {

			// 敵の座標
			aabb2 = enemy->GetAABB();

			// AABB同士の交差判定
			if (IsCollisionAABB(aabb1, aabb2)) {

				// 衝突応答
				// プレイヤーと敵の衝突時処理を呼び出す
				player_->OnCollision(enemy);
				enemy->OnCollision(player_);
			}
		}
	}

#pragma endregion
}

void GamePlayScene::ChangePhase() {
	switch (phase_) {

	case GamePlayScene::Phase::kFadeIn:

		if (fade_->IsFinished()) {
			fade_->Stop();
			phase_ = Phase::kPlay;
		}

		break;
	case GamePlayScene::Phase::kPlay:

		// デバッグカメラの更新
#ifdef _DEBUG
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isDebugCameraActive_ = !isDebugCameraActive_; // フラグをトグル
		}

		if (isDebugCameraActive_) {
			// デバッグカメラの更新
			debugCamera_->Update();
			camera_->matView = debugCamera_->GetCamera().matView;
			camera_->matProjection = debugCamera_->GetCamera().matProjection;

			// ビュープロジェクション行列の更新と転送
			camera_->TransferMatrix();

		} else {
			// ビュープロジェクション行列の更新と転送
			camera_->UpdateMatrix();
		}

#endif

		debugCamera_->Update();

		// プレイヤーの更新処理
		player_->Update();

		// 敵の更新処理
		for (auto& newEnemy : enemies_) {
			newEnemy->Update();
		}
		// enemy_->Update();

		// 全ての当たり判定を行う
		CheckAllCollisions();

		// カメラコントローラーの更新処理
		cameraController_->Update();

		skydome_->Update();

		// ブロックの更新処理
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;

				// アフィン変換行列の作成
				Matrix4x4 blockAffine = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

				worldTransformBlock->matWorld_ = blockAffine;

				// 定数バッファに転送
				worldTransformBlock->TransferMatrix();
			}
		}

		if (player_->IsDead()) {
			// 死亡演出フェーズに切り替え
			phase_ = Phase::kDeath;

			// 自キャラの座標を取得
			const Vector3& deathParticlesPosition = player_->GetWorldPosition();

			// 仮の生成処理
			deathParticles_->Initialize(playerModel_, camera_, deathParticlesPosition);
		}

		if (player_->IsClear()) {
			phase_ = Phase::kFadeOut;
		}

		break;
	case GamePlayScene::Phase::kDeath:

		// デバッグカメラの更新
#ifdef _DEBUG
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isDebugCameraActive_ = !isDebugCameraActive_; // フラグをトグル
		}

		if (isDebugCameraActive_) {
			// デバッグカメラの更新
			debugCamera_->Update();
			camera_->matView = debugCamera_->GetCamera().matView;
			camera_->matProjection = debugCamera_->GetCamera().matProjection;

			// ビュープロジェクション行列の更新と転送
			camera_->TransferMatrix();

		} else {
			// ビュープロジェクション行列の更新と転送
			camera_->UpdateMatrix();
		}

#endif

		debugCamera_->Update();

		// パーティクルが存在するとき
		if (isDeathParticlesIsExist_) {
			deathParticles_->Update();
		}

		if (deathParticles_->InFinished()) {
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			phase_ = Phase::kFadeOut;
		}

		// 敵の更新処理
		for (auto& newEnemy : enemies_) {
			newEnemy->Update();
		}

		// カメラコントローラーの更新処理
		cameraController_->Update();

		skydome_->Update();

		// ブロックの更新処理
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;

				// アフィン変換行列の作成
				Matrix4x4 blockAffine = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

				worldTransformBlock->matWorld_ = blockAffine;

				// 定数バッファに転送
				worldTransformBlock->TransferMatrix();
			}
		}

		break;

	case GamePlayScene::Phase::kFadeOut:

		// プレイヤー死亡時はタイトルに戻る
		if (player_->IsDead()) {
			if (fade_->IsFinished()) {
				SceneManager::ChangeScene(SceneManager::TITLE);
			}
		}

		// クリア時はクリアシーンに移動
		if (player_->IsClear()) {
			if (fade_->IsFinished()) {
				SceneManager::ChangeScene(SceneManager::Clear);
			}
		}

		break;

	case GamePlayScene::Phase::kPose:

		break;

	default:
		break;
	}
}

bool GamePlayScene::IsCollisionAABB(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) && (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {

		return true;
	}

	return false;
}

GamePlayScene::~GamePlayScene() {
	// ここに解放処理とか書く
	// インスタンスの持ち主のみが解放
	delete player_;
	delete playerModel_;
	delete deathParticles_;
	delete enemy_;
	delete enemyModel_;
	for (auto& newEnemy : enemies_) {
		delete newEnemy;
	}
	delete blockModel_;
	delete throughBlockModel_;
	delete deathFloor_;
	delete modelSkydome_;
	delete mapChipField_;
	delete worldTransformUtil_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
	delete sprite_;
	delete camera_;
	delete debugCamera_;
}
