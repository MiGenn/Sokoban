#pragma once
#include <fstream>
#include <vector>
#include <cassert>
#include "CstringBinarySerializer.h"
#include "PlainTypeBinarySerializer.h"
#include "TypeRegistrator.h"
#include "UniquePointerUtilities.h"

class VectorBinarySerializer final
{
public:
	VectorBinarySerializer() = delete;
	VectorBinarySerializer(const VectorBinarySerializer&) = delete;

	VectorBinarySerializer& operator=(const VectorBinarySerializer&) = delete;

	template <RegistredType T>
	static void SerializeToOpenedFile(
		const std::vector<std::unique_ptr<T>>& vector, std::ofstream& file)
	{
		int elementsCount{ (int)vector.size() };
		PlainTypeBinarySerializer::SerializeToOpenedFile(elementsCount, file);

		for (int i{ 0 }; i < elementsCount; ++i)
		{
			auto typeName{ typeid(*(vector[i].get())).name() };
			assert(SerializableObjectFactory::IsTypeRegistred(typeName));
			CstringBinarySerializer::SerializeToOpenedFile(typeName, file);
			vector[i]->SerializeToOpenedFile(file);
		}
	}

	template <RegistredType T>
	static void DeserializeFromOpenedFile(
		std::vector<std::unique_ptr<T>>& vector, std::ifstream& file)
	{
		int elementsCount;
		PlainTypeBinarySerializer::DeserializeFromOpenedFile(elementsCount, file);
		vector.clear();
		vector.reserve(elementsCount);

		for (int i{ 0 }; i < elementsCount; ++i)
			vector.emplace_back(
				UniquePointerUtilities::StaticCast<T>(SerializableObjectFactory::CreateFromOpenedFile(file)));
	}
};
