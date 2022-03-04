#pragma once
#include <vector>
#include "WinapiException.h"
#include "BitmapUnloader.h"
#include "BitmapLoader.h"
#include "Resource.h"

class ResourceManager
{
public:
	static void* GetResource(const std::wstring& relativePath, 
		const std::wstring& fullName, Loader& loader, Unloader* unloader);

	static HBITMAP GetBitmap(const std::wstring& relativePath, const std::wstring& fullName);

private:
	static std::vector<Resource*> m_resources;

	static Resource* TryFindResource(const std::wstring& relativePath, const std::wstring& fullName);
	static Resource* AddResource(const std::wstring& relativePath, 
		const std::wstring& fullName, Loader& loader, Unloader* unloader);
};
