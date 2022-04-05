#pragma once
#include <fstream>

class StringBinarySerializer final
{
public:
	StringBinarySerializer() = delete;
	StringBinarySerializer(const StringBinarySerializer&) = delete;

	StringBinarySerializer& operator=(const StringBinarySerializer&) = delete;

	static void SerializeToOpenedFile(const std::string& sourceString, std::ofstream& file);
	static void DeserializeFromOpenedFile(std::string& destinationString, std::ifstream& file);
};
