#pragma once
#include "StringUtilities.h"
#include "IBinarySerializable.h"
#include "WinapiException.h"
#include "BuildInfo.h"

class Sprite : public IBinarySerializable
{
public:
	Sprite() noexcept = default;
	Sprite(const std::wstring& fullPath);
	Sprite(Sprite&& sprite) noexcept;

	Sprite& operator=(Sprite&& right) noexcept;

	const std::wstring& GetFullRelativePath() const noexcept;
	HBITMAP GetBitmap() const noexcept;
	bool IsEmpty() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	const std::wstring* m_fullPath{ &StringUtilities::empty };
	HBITMAP m_bitmap{ NULL };

	void Initialize(const std::wstring& fullPath);
};
