#pragma once
#include "Resource.h"

class ResourceInterface
{
public:
	friend class Resource;

	ResourceInterface(const ResourceInterface& resourceInterface);
	~ResourceInterface();

	ResourceInterface& operator=(const ResourceInterface& resourceInterface);

	void* Get() const;
	void Release();

	void EnableAutoRelease();
	void DisableAutoRelease();

private:
	Resource* m_resourcePointer;
	bool m_isAutoRelease = true;

	ResourceInterface(Resource* resource);
};
