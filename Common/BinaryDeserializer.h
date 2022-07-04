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

class BinaryDeserializer
{
public:
	BinaryDeserializer() = delete;
	BinaryDeserializer(const BinaryDeserializer&) = delete;

	BinaryDeserializer& operator=(const BinaryDeserializer&) = delete;

	template<BinarySerializableAndConstructibleFromOpenedFile T>
	static void RegisterType() noexcept;
	template <BinarySerializableAndConstructibleFromOpenedFile T>
	static bool IsTypeRegistred() noexcept;
	static bool IsTypeRegistred(const std::string& typeIdentifier) noexcept;
	static IBinarySerializable* DeserializeFromOpenedFile(const std::string& typeID, std::ifstream& file);

private:
	static std::unordered_map<std::string,
		std::function<IBinarySerializable* (std::ifstream& file)>> m_creatingFunctions;

	template <BinarySerializableAndConstructibleFromOpenedFile T>
	static IBinarySerializable* CreateInstanceFromOpenedFile(std::ifstream& file);
};

template<BinarySerializableAndConstructibleFromOpenedFile T>
inline void BinaryDeserializer::RegisterType() noexcept
{
	m_creatingFunctions.emplace(
		typeid(T).name(), CreateInstanceFromOpenedFile<T>);
}

template<BinarySerializableAndConstructibleFromOpenedFile T>
inline bool BinaryDeserializer::IsTypeRegistred() noexcept
{
	return IsTypeRegistred(typeid(T).name());
}

template<BinarySerializableAndConstructibleFromOpenedFile T>
inline IBinarySerializable* BinaryDeserializer::CreateInstanceFromOpenedFile(std::ifstream& file)
{
	return new T(file);
}

