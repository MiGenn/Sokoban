#pragma once
#include <stdexcept>
#include "Vector2D.h"

template <Number T>
class Box2D : public IBinarySerializable
{
public:
	Box2D() noexcept = default;
	Box2D(Vector2D<T> position, Vector2D<T> size);
	Box2D(const Box2D<T>& box);

	Box2D<T>& operator=(const Box2D<T>& right);

	void SetPosition(Vector2D<T> newPosition) noexcept;
	void SetSize(Vector2D<T> newSize);

	Vector2D<T> GetSize() const noexcept;
	Vector2D<T> GetPosition() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	Vector2D<T> m_position;
	Vector2D<T> m_size;
};

using Box2f = Box2D<float>;
using Box2i = Box2D<int>;

template<Number T>
inline Box2D<T>::Box2D(Vector2D<T> position, Vector2D<T> size)
{
	SetPosition(position);
	SetSize(size);
}

template<Number T>
inline Box2D<T>::Box2D(const Box2D<T>& box)
{
	(*this) = box;
}

template<Number T>
inline Box2D<T>& Box2D<T>::operator=(const Box2D<T>& right)
{
	m_position = right.m_position;
	m_size = right.m_size;

	return *this;
}

template<Number T>
inline void Box2D<T>::SetPosition(Vector2D<T> newPosition) noexcept
{
	m_position = newPosition;
}

template<Number T>
inline void Box2D<T>::SetSize(Vector2D<T> newSize)
{
	static constexpr int zero{ T() };

	if (newSize.x < zero || newSize.y < zero)
		throw std::logic_error("The size is incorrect!");
}

template<Number T>
inline Vector2D<T> Box2D<T>::GetSize() const noexcept
{
	return m_size;
}

template<Number T>
inline Vector2D<T> Box2D<T>::GetPosition() const noexcept
{
	return m_position;
}

template<Number T>
inline void Box2D<T>::SerializeToOpenedFile(std::ofstream& file) const
{
	m_position.SerializeToOpenedFile(file);
	m_size.SerializeToOpenedFile(file);
}

template<Number T>
inline void Box2D<T>::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	m_position.DeserializeFromOpenedFileToSelf(file);
	m_size.DeserializeFromOpenedFileToSelf(file);
}
