#include "WstringBinarySerializer.h"

#include "CstringBinarySerializer.h"

void WstringBinarySerializer::SerializeToOpenedFile(const std::wstring& sourceString, std::ofstream& file)
{
	CstringBinarySerializer::SerializeToOpenedFile(
		reinterpret_cast<const char*>(sourceString.c_str()), file,
		((int)sourceString.size() + 1) * 2);
}

void WstringBinarySerializer::DeserializeFromOpenedFile(std::wstring& destinationString, std::ifstream& file)
{
	char* stringBuffer;
	CstringBinarySerializer::DeserializeFromOpenedFile(stringBuffer, file);
	destinationString.clear();
	destinationString = reinterpret_cast<wchar_t*>(stringBuffer);

	delete[] stringBuffer;
}
