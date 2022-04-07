#pragma once
#include <fstream>
#include <concepts>

template <typename T>
concept Integer = std::integral<T> && (!std::same_as<bool, T>);

template <typename T>
concept Number = Integer<T> || std::floating_point<T>;

template <typename T>
concept PlainType = std::integral<T> || std::floating_point<T> || std::is_enum_v<T>;

class PlainTypeBinarySerializer final
{
public:
	PlainTypeBinarySerializer() = delete;
	PlainTypeBinarySerializer(const PlainTypeBinarySerializer&) = delete;

	PlainTypeBinarySerializer& operator=(const PlainTypeBinarySerializer&) = delete;

	template<PlainType T>
	static void SerializeToOpenedFile(T sourceValue, std::ofstream& file);
	template<PlainType T>
	static void DeserializeFromOpenedFile(T& destinationValue, std::ifstream& file);
};

template<PlainType T>
inline void PlainTypeBinarySerializer::SerializeToOpenedFile(T sourceValue, std::ofstream& file)
{
	file.write(reinterpret_cast<const char*>(&sourceValue), sizeof(T));
}

template<PlainType T>
inline void PlainTypeBinarySerializer::DeserializeFromOpenedFile(T& destinationValue, std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&destinationValue), sizeof(T));
}
