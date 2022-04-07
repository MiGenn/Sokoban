#pragma once
#include "WinapiException.h"
#include "IBinarySerializable.h"
#include "BuildInfo.h"

class Sprite : public IBinarySerializable
{
public:
	Sprite() noexcept = default;
	Sprite(const std::wstring& spriteFullRalativePath) NOEXCEPT_WHEN_NDEBUG;
	Sprite(Sprite&& sprite) noexcept;

	Sprite& operator=(Sprite&& right) noexcept;

	HBITMAP GetBitmap() const noexcept;
	bool IsEmptyBitmap() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	std::wstring m_spriteFullRelativePath;
	HBITMAP m_spriteBitmap{ NULL };
};
