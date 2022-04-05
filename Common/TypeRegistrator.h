#pragma once
#include "SerializableObjectFactory.h"

template<BinarySerializableAndConstructibleFromOpenedFile T>
class TypeRegistrator
{
public:
	TypeRegistrator() noexcept
	{
		SerializableObjectFactory::RegisterType<T>();
	}

	TypeRegistrator(const TypeRegistrator&) = delete;

	TypeRegistrator& operator=(const TypeRegistrator&) = delete;
};
