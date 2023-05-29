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
Vector3& Vector3::operator-=(const Vector3& other) {
	// TODO: return ステートメントをここに挿入します
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) {
	// TODO: return ステートメントをここに挿入します
	Vector3 tmp;
	tmp.x = this->x - other.x;
	tmp.y = this->y - other.y;
	tmp.z = this->z - other.z;
	return tmp;
}

Vector3 Vector3::operator+(const Vector3& other) { 
	// TODO: return ステートメントをここに挿入します
	Vector3 tmp;
	tmp.x = this->x + other.x;
	tmp.y = this->y + other.y;
	tmp.z = this->z + other.z;
	return tmp;
	}

Vector3 Vector3::operator*(float other)const {
	Vector3 tmp;
	tmp.x = this->x * other;
	tmp.y = this->y * other;
	tmp.z = this->z * other;
	return tmp;
	
}

Vector3 Vector3::operator/(float other)const {
	// TODO: return ステートメントをここに挿入します
	Vector3 tmp;
	tmp.x = this->x / other;
	tmp.y = this->y / other;
	tmp.z = this->z / other;
	return tmp;
}


Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t) { 
	Vector3 nv1 = Vector3::Normalize(v1);
	Vector3 nv2 = Vector3::Normalize(v2);
	//Vector3 tmp;
	//ベクトル間の角度（鋭角）
	float dot = Vector3::Dot(nv1, nv2);
	if (std::abs(dot) > 0.999f) {
		return Lerp(v1, v2, t);
	}

	float angle = std::acos(dot);
	//sin
	float SinTh = std::sinf(angle);
	//補間係数
	float Ps = std::sinf(angle * (1 - t));
	float Pe = std::sinf(angle * t);
	Vector3 result = (Vector3::Multiply(Ps, nv1) +
	                 Vector3::Multiply(Pe, nv2)) / SinTh;
	return Vector3::Normalize(result);
 	
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {

	Vector3 tmp;
	tmp =Vector3::Add(v1, Vector3::Multiply(t,(Vector3::Subtract(v2,v1))));

	return tmp;
}
