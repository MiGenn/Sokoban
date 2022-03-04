#pragma once
#include "Loader.h"
#include "Unloader.h"

class Resource final
{
public:
	Resource(const std::wstring& relativePath, const std::wstring& fullName, Loader& loader, Unloader* unloader);
	Resource(const Resource&& resource);
	~Resource();

	const std::wstring& GetFullName();
	const std::wstring& GetRelativePath();

	void* Get();
	void Release();

private:
	Unloader* m_unloader;

	void* m_resource;
	std::wstring m_relativePath;
	std::wstring m_fullName;
	int m_referencesCount = 0;

	std::wstring m_pathAndName;
};
