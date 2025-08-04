#pragma once
#include <KamataEngine.h>
#include <cassert>
#include <fstream>
#include <map>
#include <sstream>

using namespace KamataEngine;

	// マップチップの種別
	enum class MapChipType {
		kBlank, // 空白
		kBlock, // ブロック
	};

class MapChipField {

	// マップチップデータ構造体
	struct MapChipData {
		std::vector<std::vector<MapChipType>> data;
	};

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

	struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	};

	struct Rect {
	    float left;
	    float right;
	    float top;
	    float bottom;
	};

	void Initialize();

	void Update();

	void Draw();

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical();

	uint32_t GetNumBlockHorizontal();
};