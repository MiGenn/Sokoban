#include "WstringBinarySerializer.h"

#include "CstringBinarySerializer.h"

void WstringBinarySerializer::SerializeToOpenedFile(const std::wstring& sourceString, std::ofstream& file)
{
	CstringBinarySerializer::SerializeToOpenedFile(
		reinterpret_cast<const char*>(sourceString.c_str()), file, (sourceString.size() + 1ull) * 2ull);
}

void WstringBinarySerializer::DeserializeFromOpenedFile(std::wstring& destinationString, std::ifstream& file)
{
	char* stringBuffer{ nullptr };
	CstringBinarySerializer::DeserializeFromOpenedFile(stringBuffer, file);
	destinationString.clear();
	destinationString = reinterpret_cast<wchar_t*>(stringBuffer);

	delete[] stringBuffer;
}
