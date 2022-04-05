#pragma once
#include <fstream>

class IntBinarySerializer final
{
public:
	IntBinarySerializer() = delete;
	IntBinarySerializer(const IntBinarySerializer&) = delete;

	IntBinarySerializer& operator=(const IntBinarySerializer&) = delete;

	static void SerializeToOpenedFile(int sourceInteger, std::ofstream& file);
	static void DeserializeFromOpenedFile(int& destinationInteger, std::ifstream& file);
};
 