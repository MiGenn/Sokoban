#include "ResourceManager.h"

#include <algorithm>

std::vector<Resource*> ResourceManager::m_resources;

ResourceInterface ResourceManager::GetResourceInterface(const std::wstring& relativePath, 
    const std::wstring& fullName, Loader& loader, Unloader* unloader)
{
    auto resource{ TryFindResource(relativePath, fullName) };
    if (!resource)
        resource = AddResource(relativePath, fullName, loader, unloader);

    return resource->GetInterface();
}

ResourceInterface ResourceManager::GetBitmapInterface(const std::wstring& relativePath, const std::wstring& fullName)
{
    auto loader{ BitmapLoader() };

    return GetResourceInterface(relativePath, fullName, loader, new BitmapUnloader());
}

Resource* ResourceManager::TryFindResource(const std::wstring& relativePath, const std::wstring& fullName)
{
    auto endIterator{ m_resources.end() };
    auto resourceIterator{ std::find_if(m_resources.begin(), endIterator,
        [&](const Resource* resource)
        {
            return resource->GetFullName() == fullName &&
                resource->GetRelativePath() == relativePath;
        }) };

    if (resourceIterator == endIterator)
        return nullptr;

    return *resourceIterator;
}

std::vector<Resource*>::iterator ResourceManager::FindResourceIterator(const Resource & resource)
{
    auto resourceInterator{ std::find_if(m_resources.begin(), m_resources.end(),
        [&](const Resource* otherResource)
        {
            return resource == (*otherResource);
        }) };

    return resourceInterator;
}

Resource* ResourceManager::AddResource(const std::wstring& relativePath,
    const std::wstring& fullName, Loader& loader, Unloader* unloader)
{
    m_resources.push_back(new Resource(relativePath, fullName, loader, unloader));

    return m_resources.back();
}

void ResourceManager::OnRelease(const Resource& resource)
{
    m_resources.erase(FindResourceIterator(resource));
}
