#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class WorldTransformUtil {

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
	/// 行列を計算し転送する関数
	/// </summary>
	/// <param name="worldTransform"></param>
	void WorldTransformUpdate(WorldTransform& worldTransform);

private:

	WorldTransform worldTransform_;

};
