#pragma once
#include<Vector3.h>

const int kColumnWidht = 60;
const int kRowHeight = 20;


Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Sub(const Vector3& v1, const Vector3& v2);
Vector3 Mul(float scalar, const Vector3& v);
float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Normalize(const Vector3& v);

