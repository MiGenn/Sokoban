#pragma once
#include <memory>
#include <string>
#include <vector>
#include "StaticConstuctor.h"
#include "Sprite.h"
#include "BuildInfo.h"

class PredefinedSprites
{
public:
	static const std::wstring wallFullPath;
	static const std::wstring roadFullPath;
	static const std::wstring crossFullPath;
	static const std::wstring barrelFullPath;
	static const std::wstring characterFullPath;

	PredefinedSprites() = delete;
	PredefinedSprites(const PredefinedSprites&) = delete;

	PredefinedSprites& operator=(const PredefinedSprites&) = delete;

	static std::shared_ptr<Sprite> GetSprite(const std::wstring& spriteFullRelativePath) NOEXCEPT_WHEN_NDEBUG;

private:
	static std::vector<std::shared_ptr<Sprite>> m_sprites;
	static StaticConstructor m_constructor;

	static void Construct() noexcept;
};
