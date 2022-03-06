#include "Resource.h"

#include "ResourceInterface.h"

Resource::Resource(const std::wstring& relativePath, 
	const std::wstring& fullName, Loader& loader, Unloader* unloader) :
	m_relativePath(relativePath), m_fullName(fullName),
	m_actualResource(loader(relativePath + fullName)), m_unloader(unloader)
{

}

Resource::~Resource()
{
	if (m_unloader)
	{
		(*m_unloader)(m_actualResource);
		delete m_unloader;
	}
}

bool Resource::operator==(const Resource& resource) const
{
	return m_actualResource == resource.m_actualResource;
}

bool Resource::operator!=(const Resource& resource) const
{
	return !((*this) == resource);
}

const std::wstring& Resource::GetFullName() const
{
	return m_fullName;
}

const std::wstring& Resource::GetRelativePath() const
{
	return m_relativePath;
}

ResourceInterface Resource::GetInterface()
{
	return { this };
}

void Resource::AddReference()
{
	++m_referencesCount;
}

void Resource::Release()
{
	--m_referencesCount;
	if (m_referencesCount == 0)
	{
		this->~Resource();
		m_unloader = nullptr;

		ResourceManager::OnRelease(*this);
	}
}
