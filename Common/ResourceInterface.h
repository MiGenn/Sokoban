#pragma once
#include "Resource.h"
#include "IBinarySerializable.h"

class ResourceInterface final : public IBinarySerializable
{
public:
	friend class Resource;

	ResourceInterface(std::ifstream& file);
	ResourceInterface(const ResourceInterface& resourceInterface);
	~ResourceInterface();

	ResourceInterface& operator=(const ResourceInterface& resourceInterface);

	const std::wstring& GetRelativePath() const;
	const std::wstring& GetFullName() const;

	void* Get() const;
	void Release();

	void EnableAutoRelease();
	void DisableAutoRelease();

	void BinarySerializeToOpenedFile(std::ofstream& file) const override;
	void BinaryDeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	Resource* m_resourcePointer;
	bool m_isAutoRelease = true;

	ResourceInterface(Resource* resource);
};
