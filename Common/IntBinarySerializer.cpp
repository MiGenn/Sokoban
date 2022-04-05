#include "IntBinarySerializer.h"

void IntBinarySerializer::SerializeToOpenedFile(int sourceInteger, std::ofstream& file)
{
	file.write(reinterpret_cast<const char*>(&sourceInteger), sizeof(int));
}

void IntBinarySerializer::DeserializeFromOpenedFile(int& destinationInteger, std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&destinationInteger), sizeof(int));
}
