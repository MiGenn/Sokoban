#pragma once
#include "IBinarySerializable.h"
#include "WinapiException.h"
#include "BuildInfo.h"

//!!!
class Sprite : public IBinarySerializable
{
public:
	Sprite() noexcept = default;
	Sprite(const std::wstring& spriteFullRalativePath);
	Sprite(Sprite&& sprite) noexcept;

	Sprite& operator=(Sprite&& right) noexcept;

	const std::wstring& GetFullRelativePath() const noexcept;
	HBITMAP GetBitmap() const noexcept;
	bool IsEmpty() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	std::wstring m_fullRelativePath;
	HBITMAP m_bitmap{ NULL };
};
