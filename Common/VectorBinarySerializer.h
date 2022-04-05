#pragma once
#include <fstream>
#include <vector>
#include <cassert>
#include "SerializableObjectFactory.h"
#include "CstringBinarySerializer.h"
#include "IntBinarySerializer.h"

class VectorBinarySerializer final
{
public:
	VectorBinarySerializer() = delete;
	VectorBinarySerializer(const VectorBinarySerializer&) = delete;

	VectorBinarySerializer& operator=(const VectorBinarySerializer&) = delete;

	template <BinarySerializable T>
	static void SerializeToOpenedFile(
		const std::vector<std::unique_ptr<T>>& vector, std::ofstream& file)
	{
		int elementsCount{ (int)vector.size() };
		IntBinarySerializer::SerializeToOpenedFile(elementsCount, file);

		for (int i{ 0 }; i < elementsCount; ++i)
		{
			auto typeName{ typeid(*(vector[i].get())).name() };
			assert(SerializableObjectFactory::IsTypeRegistred(typeName));
			CstringBinarySerializer::SerializeToOpenedFile(typeName, file);
			vector[i]->BinarySerializeToOpenedFile(file);
		}
	}

	template <BinarySerializable T>
	static void DeserializeFromOpenedFile(
		std::vector<std::unique_ptr<T>>& vector, std::ifstream& file)
	{
		int elementsCount;
		IntBinarySerializer::DeserializeFromOpenedFile(elementsCount, file);
		vector.clear();
		vector.reserve(elementsCount);

		for (int i{ 0 }; i < elementsCount; ++i)
			vector.emplace_back(SerializableObjectFactory::CreateFromOpenedFile(file));
	}
};
