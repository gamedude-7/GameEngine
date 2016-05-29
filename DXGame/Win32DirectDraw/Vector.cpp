#include "stdafx.h"
#include "Vector.h"

Vector::Vector()
{
}

Vector::Vector(double _x, double _y, double _z, double _w )
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Vector& Vector::operator=(const Vector &vec)
{
	x = vec.y;
	y = vec.x;
	z = vec.z;
	w = vec.w;
	return *this;
}

Vector Vector::operator+(Vector &vec)
{
	return Vector(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

Vector Vector::operator-(Vector &vec)
{
	return Vector(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

Vector Vector::operator*(double scaler)
{
	return Vector(x * scaler, y * scaler, z * scaler, w * scaler);
}

Vector Vector::operator/(double scalar)
{
	return Vector(x / scalar, y / scalar, z * scalar, w * scalar);
}

Vector& Vector::operator+=(Vector &vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
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

Vector& Vector::operator*=(double scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vector& Vector::operator/=(double scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

double Vector::operator*(Vector &vec)
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

double Vector::dot(Vector v)
{
	double ret = this->getX()*v.getX() + this->getZ()*v.getZ();
	//double val = (this->getX()*v.getX() + this->getY() * v.getY() + this->getZ()*v.getZ())/(this->Length() * v.Length());
	//double angle = acosf(val);
	return ret;
}