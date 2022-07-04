#pragma once
#include <fstream>
#include <concepts>
#include <CstringBinarySerializer.h>
#include <StringBinarySerializer.h>

/*
* Клас, який реалізує цей інтерфейс має зареєструвати себе за допомогою TypeRegistrator створивши його
* в .cpp файлі класу з модифікатором static. Також він повинен мати конструктор з одним параметром
* типу std::ifstream&. Перевизначаючи метод SerializeIDToOpenedFile(std::ifstream& file) const
* треба лише в його тілі викликати template<class T> SerializeIDToOpenedFile(std::ofstream& file) const 
* метод з ім'ям класу
*/
class IBinarySerializable
{
public:
	IBinarySerializable() noexcept = default;
	IBinarySerializable(const IBinarySerializable&) = delete;
	virtual ~IBinarySerializable() noexcept = default;

	IBinarySerializable& operator=(const IBinarySerializable&) = delete;

	virtual void SerializeIDToOpenedFile(std::ofstream& file) const = 0;
	static std::string DeserializeIDFromOpenedFile(std::ifstream& file);

	virtual void SerializeToOpenedFile(std::ofstream& file) const = 0;
	virtual void DeserializeFromOpenedFileToSelf(std::ifstream& file) = 0;

protected:
	template<class T>
	void SerializeIDToOpenedFile(std::ofstream& file) const;
};

template<class T>
inline void IBinarySerializable::SerializeIDToOpenedFile(std::ofstream& file) const
{
	CstringBinarySerializer::SerializeToOpenedFile(typeid(T).name(), file);
}

inline std::string IBinarySerializable::DeserializeIDFromOpenedFile(std::ifstream& file)
{
	std::string typeName;
	StringBinarySerializer::DeserializeFromOpenedFile(typeName, file);

	return typeName;
}

template<class T>
concept BinarySerializable = std::is_base_of_v<IBinarySerializable, T>;
