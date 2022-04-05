#pragma once
#include <unordered_map>
#include <memory>
#include <functional>
#include <typeinfo>
#include "IBinarySerializable.h"

template<class T>
concept BinarySerializableAndConstructibleFromOpenedFile =
BinarySerializable<T> && requires(std::ifstream& file)
{
	T(file);
};

class SerializableObjectFactory
{
public:
	SerializableObjectFactory() = delete;
	SerializableObjectFactory(const SerializableObjectFactory&) = delete;

	SerializableObjectFactory& operator=(const SerializableObjectFactory&) = delete;

	template<BinarySerializableAndConstructibleFromOpenedFile T>
	static void RegisterType() noexcept
	{
		m_creatingFunctions.emplace(
			typeid(T).name(), CreateInstanceFromOpenedFile<T>);
	}

	template <BinarySerializableAndConstructibleFromOpenedFile T>
	static bool IsTypeRegistred() noexcept
	{
		return IsTypeRegistred(typeid(T).name());
	}

	static bool IsTypeRegistred(const std::string& typeName) noexcept;

	static std::unique_ptr<IBinarySerializable> CreateFromOpenedFile(std::ifstream& file);
	static std::unique_ptr<IBinarySerializable> CreateFromOpenedFile(
		const std::string& typeName, std::ifstream& file);

private:
	static std::unordered_map<std::string,
		std::function<std::unique_ptr<IBinarySerializable>(std::ifstream& file)>> m_creatingFunctions;

	template <BinarySerializableAndConstructibleFromOpenedFile T>
	static std::unique_ptr<IBinarySerializable> CreateInstanceFromOpenedFile(std::ifstream& file)
	{
		return std::make_unique<T>(file);
	}
};
