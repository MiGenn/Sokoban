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

	template <BinarySerializable T>
	static void SerializeToOpenedFile(
		const std::vector<std::unique_ptr<T>>& vector, std::ofstream& file)
	{
		auto elementsCount{ vector.size() };
		PlainTypeBinarySerializer::SerializeToOpenedFile(elementsCount, file);

		for (size_t i{ 0ull }; i < elementsCount; ++i)
		{
			vector[i]->SerializeIDToOpenedFile(file);
			vector[i]->SerializeToOpenedFile(file);
		}
	}

	template <BinarySerializable T>
	static void DeserializeFromOpenedFile(
		std::vector<std::unique_ptr<T>>& vector, std::ifstream& file)
	{
		auto elementsCount{ 0ull };
		PlainTypeBinarySerializer::DeserializeFromOpenedFile(elementsCount, file);
		vector.clear();
		vector.reserve(elementsCount);

		for (size_t i{ 0ull }; i < elementsCount; ++i)
		{
			auto typeID{ IBinarySerializable::DeserializeIDFromOpenedFile(file) };
			auto objectRawPointer{ BinaryDeserializer::DeserializeFromOpenedFile(typeID, file) };
			vector.emplace_back(static_cast<T*>(objectRawPointer));
		}
	}
};
