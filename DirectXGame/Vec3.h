#pragma once
#include "Vector3.h"

const int kColumnWidht = 60;
const int kRowHeight = 20;

Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Sub(const Vector3& v1, const Vector3& v2);
Vector3 Mul(float scalar, const Vector3& v);
float Dot(const Vector3& v1, const Vector3& v2);
Vector3 Cross(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Normalize(const Vector3& v);
Vector3 Inverse(const Vector3& v);
float Lerp(float t, float start, float end);
Vector3 Lerp(float t, const Vector3& start, const Vector3& end);
float Clamp(float value, float min = 0.0f, float max = 1.0f);
Vector3 Project(const Vector3& v1, const Vector3& v2);