#include "ResourceInterface.h"

ResourceInterface::ResourceInterface(Resource* resource) :
	m_resourcePointer(resource)
{
	m_resourcePointer->AddReference();
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
