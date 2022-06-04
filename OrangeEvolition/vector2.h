#pragma once

template<typename T>
struct vector2
{
public:
	T x;
	T y;

	vector2();
	vector2(const T& x, const T& y);
	vector2(const vector2& vector);
	
	friend const vector2 operator+(const vector2& left, const vector2& right) {
		return vector2(left.x + right.x, left.y + right.y);
	}

	friend const vector2 operator-(const vector2& left, const vector2& right) {
		return vector2(left.x - right.x, left.y - right.y);
	}

	friend const vector2 operator*(const vector2& left, const T& right) {
		return vector2(left.x * right, left.y * right);
	}
private:
};

template<typename T>
inline vector2<T>::vector2()
{
}

template<typename T>
inline vector2<T>::vector2(const T& x, const T& y) : x(x), y(y)
{
	
}

template<typename T>
inline vector2<T>::vector2(const vector2& vector)
{
	this->x = vector.x;
	this->y = vector.y;
}