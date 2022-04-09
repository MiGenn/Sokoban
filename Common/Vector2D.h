#pragma once
#include <algorithm>
#include "WinapiException.h"
#include "IBinarySerializable.h"
#include "Serializers.h"

template<Number T>
class Vector2D final : public IBinarySerializable
{
public:
	T x = T();
	T y = T();

	Vector2D() noexcept = default;
	Vector2D(T x, T y) noexcept;
	Vector2D(const Vector2D<T>& vector);

	bool operator==(const Vector2D<T>& right) const noexcept;
	bool operator!=(const Vector2D<T>& right) const noexcept;
	Vector2D<T> operator-() noexcept;
	Vector2D<T>& operator=(const Vector2D<T>& right) noexcept;
	Vector2D<T> operator+(const Vector2D<T>& right) const noexcept;
	Vector2D<T>& operator+=(const Vector2D<T>& right) noexcept;
	Vector2D<T> operator-(const Vector2D<T>& right) const noexcept;
	Vector2D<T>& operator-=(const Vector2D<T>& right) noexcept;

	void ClampSelf(Vector2D<T> min, Vector2D<T> max) noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const noexcept override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) noexcept override;
};

using Vector2f = Vector2D<float>;
using Vector2i = Vector2D<int>;

template<Number T>
inline Vector2D<T>::Vector2D(T x, T y) noexcept
{
	this->x = x;
	this->y = y;
}

template<Number T>
inline Vector2D<T>::Vector2D(const Vector2D<T>& vector)
{
	(*this) = vector;
}

template<Number T>
inline bool Vector2D<T>::operator==(const Vector2D<T>& right) const noexcept
{
	return x == right.x && y == right.y;
}

template<Number T>
inline bool Vector2D<T>::operator!=(const Vector2D<T>& right) const noexcept
{
	return !((*this) == right);
}

template<Number T>
inline Vector2D<T> Vector2D<T>::operator-() noexcept
{
	return { -x, -y };
}

template<Number T>
inline Vector2D<T>& Vector2D<T>::operator=(const Vector2D<T>& right) noexcept
{
	x = right.x;
	y = right.y;

	return *this;
}

template<Number T>
inline Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& right) const noexcept
{
	return { x + right.x, y + right.y };
}

template<Number T>
inline Vector2D<T>& Vector2D<T>::operator+=(const Vector2D<T>& right) noexcept
{
	return (*this) = (*this) + right;
}

template<Number T>
inline Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& right) const noexcept
{
	return { x - right.x, y - right.y };
}

template<Number T>
inline Vector2D<T>& Vector2D<T>::operator-=(const Vector2D<T>& right) noexcept
{
	return (*this) = (*this) - right;
}

template<Number T>
inline void Vector2D<T>::ClampSelf(Vector2D<T> min, Vector2D<T> max) noexcept
{
	x = std::clamp(x, min.x, max.x);
	y = std::clamp(y, min.y, max.y);
}

template<Number T>
inline void Vector2D<T>::SerializeToOpenedFile(std::ofstream& file) const noexcept
{
	PlainTypeBinarySerializer::SerializeToOpenedFile(x, file);
	PlainTypeBinarySerializer::SerializeToOpenedFile(y, file);
}

template<Number T>
inline void Vector2D<T>::DeserializeFromOpenedFileToSelf(std::ifstream& file) noexcept
{
	PlainTypeBinarySerializer::DeserializeFromOpenedFile(x, file);
	PlainTypeBinarySerializer::DeserializeFromOpenedFile(y, file);
}
