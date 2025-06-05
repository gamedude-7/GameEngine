#ifndef VECTOR_H
#define VECTOR_H

//#include <math.h>
#include <windows.h>
#include <algorithm>
#include <utility>


#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

using namespace DirectX;

typedef class Vector
{
	public:
		float x, y, z, w;
		XMVECTOR vect;
		Vector();
		Vector(float _x, float _y, float _z, float _w = 0);

		float getX() const { return x; }
		float getY() const { return y; }
		float getZ() const { return z; }
		float getW() const { return w; }

		void setX(float x_) { this->x = x_; }
		void setY(float y_) { this->y = y_; }
		void setZ(float z_) { this->z = z_; }
		void setW(float w_) { this->w = w_; }

		Vector& operator=(const Vector& vec);
		Vector operator+(Vector &vec);
		Vector operator-(Vector &vec);
		Vector operator*(float scalar);
		Vector operator/(float scalar);
	 
		Vector& operator+=(Vector &vec);
		Vector& operator-=(Vector &vec);
		Vector& operator*=(float scalar);
		Vector& operator/=(float scalar);
		void operator=(Vector &vec);
		float operator*(Vector &vec);
		bool operator==(Vector &vec);
		bool operator!=(Vector &vec);
		float dot(Vector vec);
		Vector cross(Vector vec);
		
		/*Vector Perp()
		{
			return Vector(y, -x);
		}
		float Distance(Vector &vec)
		{
			Vector dvec(vec.x - x, vec.y - y);
			return sqrt(dvec.x*dvec.x + dvec.y*dvec.y);
		}

		float DistanceSq(Vector &vec)
		{
			Vector dvec(vec.x - x, vec.y - y);
			return dvec.x*dvec.x + dvec.y*dvec.y;
		}*/
		float Length()
		{
			return sqrt(x*x + y*y + z*z);
		}
		float LengthSq()
		{
			return x*x + y*y;
		}
		float Det(Vector &vec)
		{
			return x * vec.y - vec.x * y;
		}
		bool Equals(Vector &vec)
		{
			return (x == vec.x && y == vec.y);
		}

		// normalize vector , doesn't return or save the length
		void Normalize()
		{
			float length = sqrt(x*x + y*y + z*z);
			if(length != 0)
			{
				x /= length;
				y /= length;
				z /= length;
			}
		}

		void Reverse()
		{
			x = -x;
			y = -y;
		}

		float Angle() // returns in degrees
		{		
			float angle = (180.0 / 3.1415926) * atan2(-y, x);
			if(angle < 0) angle += 360;
			return angle;
		}

		float radianAngle()
		{
			float angle = (3.1415926) * atan2(-y, x);
			if(angle < 0) angle += 2*3.14;
			return angle;
		}
	private:
} Point;

#endif