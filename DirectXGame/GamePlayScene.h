#pragma once
#include <KamataEngine.h>
#include "SceneManager.h"
#include "BaseScene.h"
#include "Player.h"
#include "Skydome.h"
#include "MapChipField.h"
#include "Transform.h"
#include "WorldTransformUtil.h"
#include <vector>
#include "CameraController.h"
#include "Enemy.h"
#include "MathUtils.h"
#include "DeathParticles.h"
#include "Fade.h"

using namespace KamataEngine;
using namespace KamataEngine::MathUtils;

class GamePlayScene : public BaseScene {

	enum class Phase {
		kFadeIn,
		kPlay,
		kDeath,
		kFadeOut,
		kPose,
	};

	// ゲームの現在のフェーズ
	Phase phase_;

	Fade* fade_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライト
	Sprite* sprite_ = nullptr;

	// 3Dモデル
	Model* playerModel_ = nullptr;
	Model* enemyModel_ = nullptr;
	Model* blockModel_ = nullptr;
	Model* throughBlockModel_ = nullptr;
	Model* deathFloor_ = nullptr;
	Model* modelSkydome_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	// カメラ
	Camera* camera_ = nullptr;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = true;

	// プレイヤー
	Player* player_ = nullptr;

	// 死んだときのパーティクル
	DeathParticles* deathParticles_ = nullptr;

	// パーティクルが存在しているか
	bool isDeathParticlesIsExist_ = true;

	// 敵
	Enemy* enemy_ = nullptr;

	// 敵の発生数
	static inline const uint32_t kNumberOfEnemies =1;

	// 終了フラグ
	bool finished_ = false;

	// 敵をリスト化
	std::list<Enemy*> enemies_;

	// 天球
	Skydome* skydome_ = nullptr;

	// マップチップ
	MapChipField* mapChipField_ = nullptr;

	// ワールドトランスフォーム更新クラス
	WorldTransformUtil* worldTransformUtil_ = nullptr;

	// カメラコントローラー
	CameraController* cameraController_ = nullptr;

public:

	/// <summary>
	/// 4x4行列の積を求める関数
	/// </summary>
	/// <param name="matrix1">1つ目の行列</param>
	/// <param name="matrix2">1つ目の行列</param>
	/// <returns>4x4行列の積</returns>
	Matrix4x4 Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2);

	/// <summary>
	/// アフィン行列作成関数
	/// </summary>
	/// <param name="scale">縮尺</param>
	/// <param name="rotate">thetaを求めるための数値</param>
	/// <param name="translate">三次元座標でのx,y,zの移動量</param>
	/// <returns>アフィン行列</returns>
	Matrix4x4 MakeAffineMatrix(Vector3& scale, Vector3& rotate, Vector3& translate);

	/// <summary>
	/// 初期化関数
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 表示ブロックの生成
	/// </summary>
	void GenerateBlocks();

	// 全ての当たり判定を行う
	void CheckAllCollisions();

	// フェーズの切り替え
	void ChangePhase();

	bool IsCollisionAABB(const AABB& aabb1, const AABB& aabb2);

	// 終了フラグのゲッター
	bool InFinished() const { return finished_; }

	~GamePlayScene();

};
