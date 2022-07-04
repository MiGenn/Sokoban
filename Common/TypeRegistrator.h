#pragma once
#include "BinaryDeserializer.h"

template<BinarySerializableAndConstructibleFromOpenedFile T>
class TypeRegistrator
{
public:
	TypeRegistrator() noexcept;
	TypeRegistrator(const TypeRegistrator&) = delete;

	TypeRegistrator& operator=(const TypeRegistrator&) = delete;
};

template<BinarySerializableAndConstructibleFromOpenedFile T>
inline TypeRegistrator<T>::TypeRegistrator() noexcept
{
	BinaryDeserializer::RegisterType<T>();
}
