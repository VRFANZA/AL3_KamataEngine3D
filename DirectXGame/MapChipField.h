#pragma once
#include <KamataEngine.h>
#include <fstream>
#include <sstream>
#include <cassert>
#include <map>

using namespace KamataEngine;

// マップチップの種別
enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

// マップチップデータ構造体
struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

public:
	void Initialize();

	void Update();

	void Draw();

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical();

	uint32_t GetNumBlockHorizontal();

};