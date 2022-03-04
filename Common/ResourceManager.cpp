#include "ResourceManager.h"

#include <algorithm>

std::vector<Resource*> ResourceManager::m_resources;

void* ResourceManager::GetResource(const std::wstring& relativePath, 
    const std::wstring& fullName, Loader& loader, Unloader* unloader)
{
    auto resource{ TryFindResource(relativePath, fullName) };
    if (!resource)
        resource = AddResource(relativePath, fullName, loader, unloader);

    return resource->Get();
}

HBITMAP ResourceManager::GetBitmap(const std::wstring& relativePath, const std::wstring& fullName)
{
    auto loader{ BitmapLoader() };

    return reinterpret_cast<HBITMAP>(GetResource(relativePath, fullName, loader, new BitmapUnloader()));
}

Resource* ResourceManager::TryFindResource(const std::wstring& relativePath, const std::wstring& fullName)
{
    auto endIterator{ m_resources.end() };
    auto resourceIterator{ std::find_if(m_resources.begin(), endIterator,
        [&](Resource* resource)
        {
            return resource->GetFullName() == fullName &&
                resource->GetRelativePath() == relativePath;
        }) };

    if (resourceIterator == endIterator)
        return nullptr;

    return *resourceIterator;
}

Resource* ResourceManager::AddResource(const std::wstring& relativePath,
    const std::wstring& fullName, Loader& loader, Unloader* unloader)
{
    m_resources.push_back(new Resource(relativePath, fullName, loader, unloader));

    return m_resources.back();
}
