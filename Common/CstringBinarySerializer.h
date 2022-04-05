#pragma once
#include <fstream>

class CstringBinarySerializer
{
public:
	CstringBinarySerializer() = delete;
	CstringBinarySerializer(const CstringBinarySerializer&) = delete;

	CstringBinarySerializer& operator=(const CstringBinarySerializer&) = delete;

	static void SerializeToOpenedFile(const char* sourceCstring, std::ofstream& file, int size = 0);
	static void DeserializeFromOpenedFile(char*& destinationCstringPointer, std::ifstream& file);
};
