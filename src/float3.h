#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>
#include "prefix.h"



struct float3 {
	explicit float3() = default;
	explicit float3(f32 vX) : v { vX, vX, vX } {}
	float3(f32 v0, f32 v1, f32 v2) : v{ v0, v1, v2 } {}
	float3& operator=(const float3& rhs) = default;

	inline f32 operator[](i32 i) const { return v[i]; }
	inline f32& operator[](i32 i) { return v[i]; }

	inline const float3 operator+() const { return *this; }
	inline const float3 operator-() const { return float3(-v[0], -v[1], -v[2]); }

	inline float3 operator+=(const float3& rhs);
	inline float3 operator-=(const float3& rhs);
	inline float3 operator*=(const float3& rhs);
	inline float3 operator/=(const float3& rhs);
	inline float3 operator*=(const f32 rhs);
	inline float3 operator/=(const f32 rhs);

	inline f32 SqrLength() const;
	inline f32 Length() const;
	inline float3& Normalize();

	union {
		struct { f32 x, y, z; };
		struct { f32 r, g, b; };
		f32 v[3];
	};
};

//////////////////////////////////////////////////////////////////////////
// vec3 binary operators
inline float3 operator+(const float3& lhs, const float3& rhs) {
	return float3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

inline float3 operator-(const float3& lhs, const float3& rhs) {
	return float3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

inline float3 operator*(const float3& lhs, const float3& rhs) {
	return float3(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
}

inline float3 operator/(const float3& lhs, const float3& rhs) {
	return float3(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]);
}

inline float3 operator*(f32 lhs, const float3& rhs) {
	return float3(lhs * rhs[0], lhs * rhs[1], lhs * rhs[2]);
}

inline float3 operator*(const float3& lhs, f32 rhs) {
	return float3(rhs * lhs[0], rhs * lhs[1], rhs * lhs[2]);
}

inline float3 operator/(const float3& lhs, f32 rhs) {
	return float3(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs);
}

//////////////////////////////////////////////////////////////////////////
// compound assignment operators
inline float3 float3::operator+=(const float3& rhs) { *this = *this + rhs; return *this; }
inline float3 float3::operator-=(const float3& rhs) { *this = *this - rhs; return *this; }
inline float3 float3::operator*=(const float3& rhs) { *this = *this * rhs; return *this; }
inline float3 float3::operator/=(const float3& rhs) { *this = *this / rhs; return *this; }
inline float3 float3::operator*=(const f32 rhs) { *this = *this * rhs; return *this; }
inline float3 float3::operator/=(const f32 rhs) { *this = *this / rhs; return *this; }

//////////////////////////////////////////////////////////////////////////
// products & operations
inline f32 Dot(const float3& lhs, const float3& rhs) {
	return (lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2]);
}

inline float3 Cross(const float3& lhs, const float3& rhs) {
	f32 a = lhs.y * rhs.z - lhs.z * rhs.y;
	f32 b = lhs.z * rhs.x - lhs.x * rhs.z;
	f32 c = lhs.x * rhs.y - lhs.y * rhs.x;
	return float3(a, b, c);
}

inline f32 float3::SqrLength() const {
	return Dot(*this, *this);
}

inline f32 float3::Length() const {
	return sqrtf(Dot(*this, *this));
}

inline float3 Normalized(const float3& v) {
	return v / v.Length();
}

inline float3& float3::Normalize() {
	return *this = Normalized(*this);
}

inline float3 Lerp(const float3& a, const float3& b, const f32 t) {
	return (1 - t) * a + t * b;
}

inline float3 Reflect(const float3& v, const float3& n) {
	return v - 2 * Dot(v, n) * n;
}

inline b32 Refract(const float3& v, const float3& n, f32 nint, float3& outRefracted) {
	float3 vnorm = Normalized(v);
	f32 dt = Dot(vnorm, n);
	f32 discr = 1.0f - nint * nint * (1 - dt * dt);
	if (discr > 0) {
		outRefracted = nint * (vnorm - n * dt) - n * sqrtf(discr);
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// io
inline std::ostream& operator<<(std::ostream& os, const float3& v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

//////////////////////////////////////////////////////////////////////////
// other functions

float3 LinearToSRGB(float3 rgb) {
	return float3(std::max(1.055f * powf(rgb.r, 0.416666667f) - 0.055f, 0.0f),
				std::max(1.055f * powf(rgb.g, 0.416666667f) - 0.055f, 0.0f),
				std::max(1.055f * powf(rgb.b, 0.416666667f) - 0.055f, 0.0f));
}

float sin01(float t) {
    return .5f + .5f * sinf(t);
}
