#pragma once
#include <KamataEngine.h>

namespace KamataEngine::MathUtils {
	// ベクトル加算
    inline Vector3 Add(const Vector3& a, const Vector3& b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }

	// ベクトル減算
	inline Vector3 Sub(const Vector3& a, const Vector3& b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }

	// ベクトルのスカラー倍
    inline Vector3 Multiply(const Vector3& a, const float b) { return {a.x * b, a.y * b, a.z * b}; }

    // ベクトルのスカラー倍の逆順呼び出し
    inline Vector3 Multiply(const float b, const Vector3& a) { return {a.x * b, a.y * b, a.z * b}; }

	// ベクトル加算のオーバーロード
	inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Add(a, b); }

	// ベクトル減算のオーバーロード
	inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Sub(a, b); }

	// ベクトルのスカラー倍のオーバーロード
    inline Vector3 operator*(const Vector3& a, const float& b) { return Multiply(a, b); }

	inline Vector3 Lerp(const Vector3& a, const Vector3& b, float t) { return a + (b - a) * t; }

}