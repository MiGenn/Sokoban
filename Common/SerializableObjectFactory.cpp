#include "SerializableObjectFactory.h"

#include "StringBinarySerializer.h"

std::unordered_map<std::string, std::function<std::unique_ptr<IBinarySerializable>(std::ifstream& file)>> SerializableObjectFactory::m_creatingFunctions;

bool SerializableObjectFactory::IsTypeRegistred(const std::string& typeName) noexcept
{
	return m_creatingFunctions.contains(typeName);
}

std::unique_ptr<IBinarySerializable> SerializableObjectFactory::CreateFromOpenedFile(std::ifstream& file)
{
	std::string typeName;
	StringBinarySerializer::DeserializeFromOpenedFile(typeName, file);

	return CreateFromOpenedFile(typeName, file);
}

std::unique_ptr<IBinarySerializable> SerializableObjectFactory::CreateFromOpenedFile(
	const std::string& typeName, std::ifstream& file)
{
	auto creatingFunctionIterator{ m_creatingFunctions.find(typeName) };

	if (creatingFunctionIterator == m_creatingFunctions.end())
		throw std::runtime_error("The type is not registered!");

	return creatingFunctionIterator->second(file);
}
