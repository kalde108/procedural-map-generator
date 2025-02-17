#include "Vector3.h"

#include <cmath>

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3::Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) {}

Vector3::~Vector3() {}

Vector3 &Vector3::operator=(const Vector3 &v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3 &v) const {
	return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3 Vector3::operator-(const Vector3 &v) const {
	return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector3 Vector3::operator*(double s) const {
	return Vector3(this->x * s, this->y * s, this->z * s);
}

Vector3 Vector3::operator/(double s) const {
	return Vector3(this->x / s, this->y / s, this->z / s);
}

Vector3 &Vector3::operator+=(const Vector3 &v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vector3 &Vector3::operator*=(double s) {
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}

Vector3 &Vector3::operator/=(double s) {
	this->x /= s;
	this->y /= s;
	this->z /= s;
	return *this;
}

bool Vector3::operator==(const Vector3 &v) const {
	return this->x == v.x && this->y == v.y && this->z == v.z;
}

bool Vector3::operator!=(const Vector3 &v) const {
	return this->x != v.x || this->y != v.y || this->z != v.z;
}

double Vector3::dot(const Vector3 &v) const {
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3 cross(const Vector3 &a, const Vector3 &b) {	//
	return Vector3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

double Vector3::length() const {
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

double Vector3::lengthSquared() const {
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

Vector3 Vector3::normalize() const {
	double l = this->length();
	return Vector3(this->x / l, this->y / l, this->z / l);
}
