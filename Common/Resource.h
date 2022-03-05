#pragma once
#include "ResourceManager.h"
#include "Loader.h"
#include "Unloader.h"

class ResourceInterface;

class Resource final
{
public:
	friend class ResourceManager;
	friend class ResourceInterface;

	bool operator==(const Resource& resource) const;
	bool operator!=(const Resource& resource) const;

	const std::wstring& GetFullName() const;
	const std::wstring& GetRelativePath() const;

	ResourceInterface GetInterface();

private:
	Unloader* m_unloader;

	void* m_actualResource;
	std::wstring m_relativePath;
	std::wstring m_fullName;
	int m_referencesCount = 0;

	Resource(const std::wstring& relativePath, const std::wstring& fullName, 
		Loader& loader, Unloader* unloader);
	~Resource();

	void AddReference();
	void Release();
};
