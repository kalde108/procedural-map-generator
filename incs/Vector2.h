#ifndef VECTOR2_H
# define VECTOR2_H

class Vector2 {
public:
	Vector2();
	Vector2(double x, double y);
	Vector2(const Vector2 &v);
	~Vector2();

	Vector2 &operator=(const Vector2 &v);
	Vector2 operator+(const Vector2 &v) const;
	Vector2 operator-(const Vector2 &v) const;
	Vector2 operator*(double s) const;
	Vector2 operator/(double s) const;
	Vector2 &operator+=(const Vector2 &v);
	Vector2 &operator-=(const Vector2 &v);
	Vector2 &operator*=(double s);
	Vector2 &operator/=(double s);
	bool operator==(const Vector2 &v) const;
	bool operator!=(const Vector2 &v) const;

	double dot(const Vector2 &v) const;
	double length() const;
	double lengthSquared() const;
	Vector2 normalize() const;

	double x, y;
};

#endif
