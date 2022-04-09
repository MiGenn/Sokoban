#pragma once
#include "SerializableObjectFactory.h"

template<class T>
concept RegistredType = BinarySerializable<T> && requires(T instance)
{
	{ instance.IsRegistred() } -> std::same_as<bool>; //////////
};

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
	SerializableObjectFactory::RegisterType<T>();
}
