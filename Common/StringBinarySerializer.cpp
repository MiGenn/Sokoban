#include "StringBinarySerializer.h"

#include "CstringBinarySerializer.h"

void StringBinarySerializer::SerializeToOpenedFile(const std::string& sourceString, std::ofstream& file)
{
	CstringBinarySerializer::SerializeToOpenedFile(sourceString.c_str(), file, sourceString.size() + 1ull);
}

void StringBinarySerializer::DeserializeFromOpenedFile(std::string& destinationString, std::ifstream& file)
{
	char* stringBuffer{ nullptr };
	CstringBinarySerializer::DeserializeFromOpenedFile(stringBuffer, file);
	destinationString.clear();
	destinationString = stringBuffer;

	delete[] stringBuffer;
}
