#include "CstringBinarySerializer.h"

#include "PlainTypeBinarySerializer.h"

void CstringBinarySerializer::SerializeToOpenedFile(const char* sourceCstring, std::ofstream& file, size_t size)
{
	if (size <= 0ull)
		size = strlen(sourceCstring) + 1ull;

	PlainTypeBinarySerializer::SerializeToOpenedFile(size, file);
	file.write(sourceCstring, size);
}

void CstringBinarySerializer::DeserializeFromOpenedFile(char*& destinationCstringPointer, std::ifstream& file)
{
	size_t stringSizeInBytes{ 0ull };
	PlainTypeBinarySerializer::DeserializeFromOpenedFile(stringSizeInBytes, file);
	auto cstring{ std::make_unique<char[]>(stringSizeInBytes)};
	file.read(cstring.get(), stringSizeInBytes);
	destinationCstringPointer = cstring.release();
}
