#include "StringBinarySerializer.h"

#include "CstringBinarySerializer.h"

void StringBinarySerializer::SerializeToOpenedFile(const std::string& sourceString, std::ofstream& file)
{
	CstringBinarySerializer::SerializeToOpenedFile(sourceString.c_str(), file, 
		(int)sourceString.size() + 1);
}

void StringBinarySerializer::DeserializeFromOpenedFile(std::string& destinationString, std::ifstream& file)
{
	char* stringBuffer;
	CstringBinarySerializer::DeserializeFromOpenedFile(stringBuffer, file);
	destinationString.clear();
	destinationString = stringBuffer;

	delete[] stringBuffer;
}
