#pragma once
#include <random>
#include "world_config.h"

template<typename T>
struct vector2
{
public:
	T x;
	T y;

	vector2();
	vector2(const T& x, const T& y);
	vector2(const vector2& vector);
	
	void set_position(const T& x, const T& y);
	void set_x(const T& x);
	void set_y(const T& y);

	static const vector2 random(int maxX, int maxY) {
		return vector2(1 + rand() % maxX, 1 + rand() % maxY);
	}

	friend const vector2 operator+(const vector2& left, const vector2& right) {
		return vector2(left.x + right.x, left.y + right.y);
	}

	friend const vector2 operator-(const vector2& left, const vector2& right) {
		return vector2(left.x - right.x, left.y - right.y);
	}

	friend const vector2 operator*(const vector2& left, const T& right) {
		return vector2(left.x * right, left.y * right);
	}
};

template<typename T>
inline vector2<T>::vector2() : x(0), y(0)
{
	
}

template<typename T>
inline vector2<T>::vector2(const T& x, const T& y)
{
	set_position(x, y);
}

template<typename T>
inline vector2<T>::vector2(const vector2& vector)
{
	set_position(vector.x, vector.y);
}

template<typename T>
inline void vector2<T>::set_position(const T& x, const T& y)
{
	set_x(x);
	set_y(y);
}

template<typename T>
inline void vector2<T>::set_x(const T& x)
{
	this->x = x;
	if (x > world_size_x) this->x = world_size_x;
	else if (x < 1) this->x = 1;
}

template<typename T>
inline void vector2<T>::set_y(const T& y)
{
	this->y = y;
	if (y > world_size_y) this->y = world_size_y;
	else if (y < 1) this->y = 1;
}
