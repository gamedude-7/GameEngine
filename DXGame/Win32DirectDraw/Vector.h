#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>


typedef class Vector
{
	public:
		double x, y, z, w;
		Vector();
		Vector(double _x, double _y, double _z, double _w = 0); 

		double getX() const { return x; }
		double getY() const { return y; }
		double getZ() const { return z; }
		double getW() const { return w; }

		void setX(double x_) { this->x = x_; }
		void setY(double y_) { this->y = y_; }
		void setZ(double z_) { this->z = z_; }
		void setW(double w_) { this->w = w_; }

		Vector& operator=(const Vector &vec);
		Vector operator+(Vector &vec);
		Vector operator-(Vector &vec);
		Vector operator*(double scalar);
		Vector operator/(double scalar);
		Vector& operator+=(Vector &vec);
		Vector& operator-=(Vector &vec);
		Vector& operator*=(double scalar);
		Vector& operator/=(double scalar);
		void operator=(Vector &vec);
		double operator*(Vector &vec);
		bool operator==(Vector &vec);
		bool operator!=(Vector &vec);
		double dot(Vector vec);
		
		/*Vector Perp()
		{
			return Vector(y, -x);
		}
		double Distance(Vector &vec)
		{
			Vector dvec(vec.x - x, vec.y - y);
			return sqrt(dvec.x*dvec.x + dvec.y*dvec.y);
		}

		double DistanceSq(Vector &vec)
		{
			Vector dvec(vec.x - x, vec.y - y);
			return dvec.x*dvec.x + dvec.y*dvec.y;
		}*/
		double Length()
		{
			return sqrt(x*x + y*y + z*z);
		}
		double LengthSq()
		{
			return x*x + y*y;
		}
		double Det(Vector &vec)
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
			double length = sqrt(x*x + y*y + z*z);
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

		double Angle() // returns in degrees
		{		
			double angle = (180.0 / 3.1415926) * atan2(-y, x);
			if(angle < 0) angle += 360;
			return angle;
		}

		double radianAngle()
		{
			double angle = (3.1415926) * atan2(-y, x);
			if(angle < 0) angle += 2*3.14;
			return angle;
		}
	private:
} Point;

#endif