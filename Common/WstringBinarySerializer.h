#pragma once
#include <fstream>

class WstringBinarySerializer final
{
public:
	WstringBinarySerializer() = delete;
	WstringBinarySerializer(const WstringBinarySerializer&) = delete;

	WstringBinarySerializer& operator=(const WstringBinarySerializer&) = delete;

	static void SerializeToOpenedFile(const std::wstring& sourceString, std::ofstream& file);
	static void DeserializeFromOpenedFile(std::wstring& destinationString, std::ifstream& file);
};
