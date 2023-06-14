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

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	return{ v1.y * v2.z - v1.z * v2.y,v1.z * v2.x - v1.x * v2.z,v1.x * v2.y - v1.y * v2.x };
}

float Length(const Vector3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(const Vector3& v) {
	float len = Length(v);
	return { v.x / len,v.y / len,v.z / len };
}

Vector3 Inverse(const Vector3& v) {
	return{ -v.x,-v.y,-v.z };
}

float Clamp(float value, float min, float max) {
	if (value <= min) {
		return min;
	}
	if (value >= max) {
		return max;
	}
	return value;
}

float Lerp(float t, float start, float end) {
	Clamp(t);
	return(1.0f - t) * start + t * end;
}

Vector3 Lerp(float t, const Vector3& start, const Vector3& end) {
	return{ Lerp(t,start.x,end.x),Lerp(t,start.y,end.y),Lerp(t,start.z,end.z) };
}

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	
	float t = Dot(v1, v2) / std::powf(Length(v2), 2);

	t = Clamp(t);

	return Mul(t, v2);
}