#pragma once
#include <unordered_map>
#include "WinapiException.h"
#include "StaticConstuctor.h"
#include "BuildInfo.h"

class Sprites
{
public:
	static const std::wstring wallFullRelativePath;
	static const std::wstring roadFullRelativePath;
	static const std::wstring crossFullRelativePath;
	static const std::wstring barrelFullRelativePath;
	static const std::wstring characterFullRelativePath;

	Sprites() = delete;
	Sprites(const Sprites&) = delete;

	Sprites& operator=(const Sprites&) = delete;

	static class Sprite GetSprite(const std::wstring& spriteFullRelativePath) NOEXCEPT_WHEN_NDEBUG;
	static HBITMAP GetRawSprite(const std::wstring& spriteFullRelativePath) NOEXCEPT_WHEN_NDEBUG;

private:
	static std::unordered_map<std::wstring, HBITMAP> m_sprites;
	static StaticConstructor m_constructor;

	static void Construct() noexcept;
};
