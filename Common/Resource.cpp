#include "Resource.h"

Resource::Resource(const std::wstring& relativePath, 
	const std::wstring& fullName, Loader& loader, Unloader* unloader) :
	m_relativePath(relativePath), m_fullName(fullName),
	m_resource(loader(relativePath + fullName)), m_unloader(unloader)
{
	
}

Resource::Resource(const Resource&& resource) : 
	m_referencesCount(resource.m_referencesCount),
	m_relativePath(resource.m_relativePath),
	m_fullName(resource.m_fullName),
	m_resource(resource.m_resource)
{
	m_resource = nullptr;
}

Resource::~Resource()
{
	(*m_unloader)(m_resource);
	delete m_unloader;
}

const std::wstring& Resource::GetFullName()
{
	return m_fullName;
}

const std::wstring& Resource::GetRelativePath()
{
	return m_relativePath;
}

void* Resource::Get()
{
	++m_referencesCount;

	return m_resource;
}

void Resource::Release()
{
	--m_referencesCount;
}
