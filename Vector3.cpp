#include"Vector3.h"

Vector3 Vector3::Add(const Vector3& v1, const Vector3& v2)
{
	Vector3  temp;
	temp.x = v1.x + v2.x;
	temp.y = v1.y + v2.y;
	temp.z = v1.z + v2.z;

	return Vector3(temp);
}

Vector3 Vector3::Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3  temp;
	temp.x = v1.x - v2.x;
	temp.y = v1.y - v2.y;
	temp.z = v1.z - v2.z;
	return Vector3(temp);
}

Vector3 Vector3::Multiply(float scalar, const Vector3& v)
{
	Vector3  temp;
	temp.x = v.x * scalar;
	temp.y = v.y * scalar;
	temp.z = v.z * scalar;
	return Vector3(temp);
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2)
{
	float temp;
	temp = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return temp;
}

float Vector3::Length(const Vector3& v)
{
	float temp;
	
	temp = sqrtf( pow(v.x,2.0f)+ pow(v.y,2.0f)+ pow(v.z,2.0f));
	return temp;
}

Vector3 Vector3::Normalize(const Vector3& v)
{
	Vector3 temp;
	temp.x = v.x / v.Length(v);
	temp.y = v.y / v.Length(v);
	temp.z = v.z / v.Length(v);

	return Vector3(temp);
}

Vector3& Vector3::operator+=(const Vector3& other) {
	// TODO: return ステートメントをここに挿入します
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}



