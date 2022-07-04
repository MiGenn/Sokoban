#include "BinaryDeserializer.h"

#include "StringBinarySerializer.h"

std::unordered_map<std::string, std::function<IBinarySerializable* (std::ifstream& file)>>
BinaryDeserializer::m_creatingFunctions;

bool BinaryDeserializer::IsTypeRegistred(const std::string& typeIdentifier) noexcept
{
	return m_creatingFunctions.contains(typeIdentifier);
}

IBinarySerializable* BinaryDeserializer::DeserializeFromOpenedFile(
	const std::string& typeID, std::ifstream& file)
{
	auto creatingFunctionIterator{ m_creatingFunctions.find(typeID) };
	if (creatingFunctionIterator == m_creatingFunctions.end())
		throw std::runtime_error("The type is not registered!");

	return creatingFunctionIterator->second(file);
}
