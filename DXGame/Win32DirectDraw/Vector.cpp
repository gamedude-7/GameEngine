#include "stdafx.h"
#include "Vector.h"

Vector::Vector() 
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
	vect = XMVectorSet(x, y, z, w);
}

Vector::Vector(float _x, float _y, float _z, float _w )
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
	vect = XMVectorSet(x, y, z, w);
}

Vector& Vector::operator=(const Vector &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
	vect = XMVectorSet(x, y, z, w);
	return *this;
}

Vector Vector::operator+(Vector &vec)
{
	x = x + vec.x;
	y = y + vec.y;
	z = z + vec.z;
	w = w + vec.w;
	vect = XMVectorSet(x, y , z, w);	
	return Vector(x, y, z, w);
}

Vector Vector::operator-(Vector &vec)
{
	vect = XMVectorSet(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	return Vector(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

Vector Vector::operator*(float scaler)
{
	return Vector(x * scaler, y * scaler, z * scaler, w * scaler);
}

Vector Vector::operator/(float scalar)
{
	return Vector(x / scalar, y / scalar, z * scalar, w * scalar);
}

Vector& Vector::operator+=(Vector &vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	XMVectorSetX(vect,x);
	XMVectorSetY(vect, y);
	XMVectorSetZ(vect, z);
	XMVectorSetW(vect, w);
	return *this;
}

Vector& Vector::operator-=(Vector &vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
	return *this;
}

Vector& Vector::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vector& Vector::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

float Vector::operator*(Vector &vec)
{
	return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

bool Vector::operator==(Vector &vec)
{
	return (x == vec.x && y == vec.y && z == vec.z && w == vec.w);
}

bool Vector::operator!=(Vector &vec)
{
	return (x != vec.x || y != vec.y && z != vec.z && w != vec.w);
}

void Vector::operator=(Vector &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
	vect = XMVectorSet(x, y, z, w);
}

float Vector::dot(Vector v)
{
	float ret = this->getX()*v.getX() + this->getY() * v.getY() + this->getZ()*v.getZ();
	//float val = (this->getX()*v.getX() + this->getY() * v.getY() + this->getZ()*v.getZ())/(this->Length() * v.Length());
	//float angle = acosf(val);
	return ret;
}

Vector Vector::cross(Vector v)
{
	Vector ret;
	ret.x = this->getY() * v.getZ() - this->getZ() * v.getY();
	ret.y = this->getZ() * v.getX() - this->getX() * v.getZ();
	ret.z = this->getX() * v.getY() - this->getY() * v.getX();
	return ret;
}