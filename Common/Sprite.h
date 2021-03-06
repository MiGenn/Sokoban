#pragma once
#include "StringUtilities.h"
#include "IBinarySerializable.h"
#include "WinapiException.h"
#include "BuildInfo.h"

class Sprite final : public IBinarySerializable
{
public:
	Sprite() noexcept = default;
	Sprite(const std::wstring& fullPath);
	Sprite(const Sprite& sprite) noexcept;
	Sprite(Sprite&& sprite) noexcept;

	Sprite& operator=(const Sprite& right) noexcept;
	Sprite& operator=(Sprite&& right) noexcept;

	const std::wstring& GetFullPath() const noexcept;
	HBITMAP GetBitmap() const noexcept;
	bool IsEmpty() const noexcept;

	void SerializeIDToOpenedFile(std::ofstream& file) const override;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	std::wstring m_fullPath;
	HBITMAP m_bitmap{ nullptr };

	void InitializeBitmap();
};
