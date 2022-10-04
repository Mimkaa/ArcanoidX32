#pragma once
#include "CommonMath.h"

template <typename T>
class _Vec2
{
public:
	_Vec2() = default;

	_Vec2(T x, T y) :x(x), y(y){};

	_Vec2(const _Vec2& another) :_Vec2(another.x, another.y){};

	template <typename T2>
	explicit operator _Vec2<T2>() const
	{
		return { (T2)x,(T2)y };
	}
	
	_Vec2& operator=(const _Vec2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	_Vec2& operator - ()
	{
		x = -x;
		y = -y;
		return *this;
	}

	_Vec2& operator () (const _Vec2& other)
	{
		x = other.x;
		y = other.y;
		return (*this);
	}
	_Vec2& operator += (const _Vec2& other)
	{
		x += other.x;
		y += other.y;
		return (*this);
	}
	_Vec2 operator + (const _Vec2& other) const
	{
		return _Vec2(*this) += other;
	}
	_Vec2& operator -= (const _Vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return (*this);
	}
	_Vec2 operator - (const _Vec2& other) const
	{
		return _Vec2(*this) -= other;
	}
	_Vec2& operator *= (const T val)
	{
		x *= val;
		y *= val;
		return (*this);
	}
	_Vec2 operator * (const T val) const
	{
		return _Vec2(*this) *= val;
	}

	_Vec2& operator /= (const T val)
	{
		x /= val;
		y /= val;
		return (*this);
	}
	_Vec2 operator / (const T val) const
	{
		return _Vec2(*this) /= val;
	}

	T LenSq() const
	{
		return sq(*this);
	}
	T Len() const
	{
		return sqrt(LenSq());
	}
	_Vec2& Normalize()
	{
		T length = Len();
		x /= length;
		y /= length;
		return (*this);
	}
	_Vec2	GetNormalized() const
	{
		_Vec2 norm = *this;
		norm.Normalize();
		return norm;
	}

	T		operator*(const _Vec2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

public:
	T x;
	T y;
};

typedef _Vec2<float> Vec2;
typedef _Vec2<double> Ved2;
typedef _Vec2<int> Vei2;
