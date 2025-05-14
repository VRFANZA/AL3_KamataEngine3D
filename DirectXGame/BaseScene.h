#pragma once
class BaseScene {
public:

	/// <summary>
	/// 初期化関数
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新関数
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画関数
	/// </summary>
	virtual void Draw();
};
