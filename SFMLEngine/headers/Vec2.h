#pragma once
/*
	This is a custom made wrapper for the Vector2 class in SFML, used mainly to be user friendly
	it will work with all the sfml functions as if it was an sf::Vector2<T> object.
	It contains all the differnet implicet and explicit conversaions from one data type to another.
	If you find any problems to this files or have any suggestions to add, make a pull request or
	send an email to: seif_sallam@aucegypt.edu

	Note: it is also user friendly with the standard output stream

	@[NOTE: Seif] Added box2d Vectors
*/

#include <iostream>
#include <math.h>
#include "SFML/System/Vector2.hpp"
#include "box2d/b2_math.h"

template<class T>
class Vec2 {
public:
	union {
		struct {
			T x, y;
		};
		struct {
			T w, h;
		};
	};
	inline Vec2() : x(T()), y(T()) {}
	inline Vec2(const sf::Vector2<T>& sfVec2) : x(sfVec2.x), y(sfVec2.y) {}
	inline Vec2(const b2Vec2& vec) : x(vec.x), y(vec.y) {}
	inline Vec2(const T& x, const T& y) : x(x), y(y) {}
	inline Vec2(const Vec2<T>& vec2) : x(vec2.x), y(vec2.y) {}
	inline Vec2<T>& operator=(const Vec2& vec2) { x = vec2.x; y = vec2.y; return *this; }
	inline Vec2<T>& Zero() { x = 0; y = 0; return *this; }
	inline Vec2<T>& One() { x = 0; y = 0; return *this; }
	inline Vec2<T>& Normalize() {
		double length = sqrt(pow(x, 2) + pow(y, 2));
		x = x / length;
		y = y / length;
		return *this;
	}

	template<class U = T>
	inline sf::Vector2<U> sfVec()
	{
		return sf::Vector2<U>(x, y);
	}

	inline b2Vec2 B2Vec() { return b2Vec2(x, y); }
	inline operator b2Vec2() { return b2Vec2(x, y); }
	inline operator sf::Vector2<T>() { return sf::Vector2<T>((T)x, (T)y); }
	inline operator Vec2<float>() { return Vec2<float>((float)x, (float)y); }
	inline operator Vec2<uint32_t>() { return Vec2<uint32_t>((uint32_t)x, (uint32_t)y); }
	inline operator Vec2<int32_t>() { return Vec2<int32_t>((int32_t)x, (int32_t)y); }
	inline operator Vec2<double>() { return Vec2<double>((double)x, (double)y); }
	
	inline friend std::ostream& operator<<(std::ostream& stream, const Vec2<T>& vec) {
		stream << "(" << vec.x << ", " << vec.y << ")";
		return stream;
	}

	inline Vec2<T> operator+(const Vec2<T>& vec)
	{
		return Vec2<T>(x + vec.x, y + vec.y);
	}
	inline Vec2<T> operator-(const Vec2<T>& vec)
	{
		return Vec2<T>(x - vec.x, y - vec.y);
	}
	inline Vec2<T> operator-=(const Vec2<T>& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	inline Vec2<T> operator+=(const Vec2<T>& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	inline Vec2<T> operator*(const Vec2<T>& vec)
	{
		return Vec2<T>(x * vec.x, y * vec.y);
	}
	inline Vec2<T> operator*(const T& scaler)
	{
		return Vec2<T>(x * scaler, y * scaler);
	}
	inline Vec2<T> operator*=(const T& scaler)
	{
		x *= scaler;
		y *= scaler;
		return *this;
	}
	inline Vec2<T> operator*=(const Vec2<T>& vec)
	{
		x *= vec.x;
		y *= vec.y;
		return *this;
	}

	inline Vec2<T> operator/(const T& scaler)
	{
		if (scaler == 0)
			return Vec2<T>();
		return Vec2<T>(x / scaler, y / scaler);
	}
	inline Vec2<T> operator/= (const T& scaler)
	{
		if (scaler == 0)
			return Vec2<T>();
		x /= scaler;
		y /= scaler;
		return *this;
	}
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int32_t>;
using Vec2u = Vec2<uint32_t>;
using Vec2d = Vec2<double>;