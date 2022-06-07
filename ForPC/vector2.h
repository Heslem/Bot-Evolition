#pragma once
#include <random>
#include "world_config.h"

template<typename T>
struct vector2
{
private:
	T x;
	T y;
public:
	vector2();
	vector2(const T& x, const T& y);
	vector2(const vector2& vector);
	
	T get_x() const { return x; }
	T get_y() const { return y; }
	void set_position(const T& x, const T& y);
	bool set_x(const T& x);
	bool set_y(const T& y);

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
inline bool vector2<T>::set_x(const T& x)
{
	this->x = x;
	if (x > world_size_x) {
		this->x = world_size_x; return true;
	}
	else if (x < 1) {
		this->x = 1; return true;
	}

	return false;
}

template<typename T>
inline bool vector2<T>::set_y(const T& y)
{
	this->y = y;
	if (y > world_size_y) { 
		this->y = world_size_y; return true; 
	}
	else if (y < 1) {
		this->y = 1; return true;
	}
	return false;
}
