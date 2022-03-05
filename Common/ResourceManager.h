#pragma once
#include <vector>
#include "BitmapUnloader.h"
#include "BitmapLoader.h"
#include "ResourceInterface.h"

class ResourceInterface;

class ResourceManager
{
public:
	friend class Resource;

	static ResourceInterface GetResourceInterface(const std::wstring& relativePath, 
		const std::wstring& fullName, Loader& loader, Unloader* unloader);

	static ResourceInterface GetBitmapInterface(const std::wstring& relativePath, const std::wstring& fullName);

private:
	static std::vector<Resource*> m_resources;

	static Resource* TryFindResource(const std::wstring& relativePath, const std::wstring& fullName);
	static std::vector<Resource*>::iterator FindResourceIterator(const Resource& resource);

	static Resource* AddResource(const std::wstring& relativePath, 
		const std::wstring& fullName, Loader& loader, Unloader* unloader);

	static void OnRelease(const Resource& resource);
};
