#include "ResourceInterface.h"

#include "WstringBinarySerializer.h"

ResourceInterface::ResourceInterface(Resource* resource) :
	m_resourcePointer(resource)
{
	m_resourcePointer->AddReference();
}

ResourceInterface::ResourceInterface(std::ifstream& file)
{
	BinaryDeserializeFromOpenedFileToSelf(file);
}

ResourceInterface::ResourceInterface(const ResourceInterface& resourceInterface) :
	m_resourcePointer(resourceInterface.m_resourcePointer), 
	m_isAutoRelease(resourceInterface.m_isAutoRelease)
{
	m_resourcePointer->AddReference();
}

ResourceInterface::~ResourceInterface()
{
	if (m_isAutoRelease && m_resourcePointer)
		m_resourcePointer->Release();
}

ResourceInterface& ResourceInterface::operator=(const ResourceInterface& resourceInterface)
{
	m_resourcePointer = resourceInterface.m_resourcePointer;
	m_isAutoRelease = resourceInterface.m_isAutoRelease;
	m_resourcePointer->AddReference();

	return *this;
}

const std::wstring& ResourceInterface::GetFullName() const
{
	return m_resourcePointer->GetFullName();
}

const std::wstring& ResourceInterface::GetRelativePath() const
{
	return m_resourcePointer->GetRelativePath();
}

void* ResourceInterface::Get() const
{
	return m_resourcePointer->m_actualResource;
}

void ResourceInterface::Release()
{
	if (m_resourcePointer)
	{
		m_resourcePointer->Release();
		m_resourcePointer = nullptr;
	}
}

void ResourceInterface::EnableAutoRelease()
{
	m_isAutoRelease = true;
}

void ResourceInterface::DisableAutoRelease()
{
	m_isAutoRelease = false;
}

void ResourceInterface::BinarySerializeToOpenedFile(std::ofstream& file) const
{
	
	WstringBinarySerializer::SerializeToOpenedFile(GetRelativePath(), file);
	WstringBinarySerializer::SerializeToOpenedFile(GetFullName(), file);
}

void ResourceInterface::BinaryDeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	this->~ResourceInterface();

	

	std::wstring relativePath;
	WstringBinarySerializer::DeserializeFromOpenedFile(relativePath, file);
	std::wstring fullName;
	WstringBinarySerializer::DeserializeFromOpenedFile(fullName, file);
	//m_resourcePointer = ResourceManager::GetResourceInterface(relativePath, fullName, )
}
