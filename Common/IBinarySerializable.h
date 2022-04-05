#pragma once
#include <fstream>

class IBinarySerializable
{
public:
	IBinarySerializable() noexcept = default;
	IBinarySerializable(const IBinarySerializable&) = delete;

	IBinarySerializable& operator=(const IBinarySerializable&) = delete;

	virtual void BinarySerializeToOpenedFile(std::ofstream& file) const = 0;
	virtual void BinaryDeserializeFromOpenedFileToSelf(std::ifstream& file) = 0;
};

template<class T>
concept BinarySerializable = std::derived_from<T, IBinarySerializable>;
