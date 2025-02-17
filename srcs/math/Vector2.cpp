#include <cmath>

#include "Vector2.h"

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(double x, double y) : x(x), y(y) {}

Vector2::Vector2(const Vector2 &v) : x(v.x), y(v.y) {}

Vector2::~Vector2() {}

Vector2 &Vector2::operator=(const Vector2 &v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2 &v) const
{
	return Vector2(this->x + v.x, this->y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v) const
{
	return Vector2(this->x - v.x, this->y - v.y);
}

Vector2 Vector2::operator*(double s) const
{
	return Vector2(this->x * s, this->y * s);
}

Vector2 Vector2::operator/(double s) const
{
	return Vector2(this->x / s, this->y / s);
}

Vector2 &Vector2::operator+=(const Vector2 &v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2 &Vector2::operator*=(double s)
{
	this->x *= s;
	this->y *= s;
	return *this;
}

Vector2 &Vector2::operator/=(double s)
{
	x /= s;
	y /= s;
	return *this;
}

bool Vector2::operator==(const Vector2 &v) const
{
	return this->x == v.x && this->y == v.y;
}

bool Vector2::operator!=(const Vector2 &v) const
{
	return this->x != v.x || this->y != v.y;
}

double Vector2::dot(const Vector2 &v) const
{
	return this->x * v.x + this->y * v.y;
}

double Vector2::length() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

double Vector2::lengthSquared() const
{
	return this->x * this->x + this->y * this->y;
}

Vector2 Vector2::normalize() const
{
	double l = this->length();
	if (l == 0)
		return Vector2(0, 0);
	return Vector2(this->x / l, this->y / l);
}
