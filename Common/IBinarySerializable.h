#pragma once
#include <fstream>
#include <concepts>

class IBinarySerializable
{
public:
	IBinarySerializable() noexcept = default;
	IBinarySerializable(const IBinarySerializable&) = delete;
	virtual ~IBinarySerializable() noexcept = default;

	IBinarySerializable& operator=(const IBinarySerializable&) = delete;

	virtual void SerializeToOpenedFile(std::ofstream& file) const = 0;
	virtual void DeserializeFromOpenedFileToSelf(std::ifstream& file) = 0;

	constexpr virtual bool IsRegistred() const noexcept;
};

template<class T>
concept BinarySerializable = std::is_base_of_v<IBinarySerializable, T>;

constexpr bool IBinarySerializable::IsRegistred() const noexcept
{
	return false;
}
