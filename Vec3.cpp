#include"Vec3.h"
#include<cmath>


Vector3 Add(const Vector3& v1, const Vector3& v2) {
    return { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
}

Vector3 Sub(const Vector3& v1, const Vector3& v2) {
	return { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
}

Vector3 Mul(float scalar, const Vector3& v) {
	return { scalar * v.x,scalar * v.y,scalar * v.z };
}

float Dot(const Vector3& v1, const Vector3& v2) {
	return { v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
}

float Length(const Vector3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(const Vector3& v) {
	float len = Length(v);
	return { v.x / len,v.y / len,v.z / len };
}

