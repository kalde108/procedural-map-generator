#ifndef VECTOR3_H
# define VECTOR3_H

class Vector3 {
public:
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(const Vector3 &v);
	~Vector3();

	Vector3 &operator=(const Vector3 &v);
	Vector3 operator+(const Vector3 &v) const;
	Vector3 operator-(const Vector3 &v) const;
	Vector3 operator*(double s) const;
	Vector3 operator/(double s) const;
	Vector3 &operator+=(const Vector3 &v);
	Vector3 &operator-=(const Vector3 &v);
	Vector3 &operator*=(double s);
	Vector3 &operator/=(double s);
	bool operator==(const Vector3 &v) const;
	bool operator!=(const Vector3 &v) const;
	
	double dot(const Vector3 &v) const;
	Vector3 cross(const Vector3 &v) const;
	double length() const;
	double lengthSquared() const;
	Vector3 normalize() const;

	double x, y, z;
};

#endif
