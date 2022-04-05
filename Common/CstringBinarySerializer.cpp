#include "CstringBinarySerializer.h"

#include "IntBinarySerializer.h"

void CstringBinarySerializer::SerializeToOpenedFile(const char* sourceCstring, std::ofstream& file, int size)
{
	if (size == 0)
		size = (int)strlen(sourceCstring);

	IntBinarySerializer::SerializeToOpenedFile(size, file);
	file.write(sourceCstring, size);
}

void CstringBinarySerializer::DeserializeFromOpenedFile(char*& destinationCstringPointer, std::ifstream& file)
{
	int stringSizeInBytes;
	IntBinarySerializer::DeserializeFromOpenedFile(stringSizeInBytes, file);
	auto cstring{ std::make_unique<char[]>(stringSizeInBytes)};
	file.read(cstring.get(), stringSizeInBytes);
	destinationCstringPointer = cstring.release();
}
