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
	static const std::wstring wallFullRelativePath;
	static const std::wstring roadFullRelativePath;
	static const std::wstring crossFullRelativePath;
	static const std::wstring barrelFullRelativePath;
	static const std::wstring characterFullRelativePath;

	PredefinedSprites() = delete;
	PredefinedSprites(const PredefinedSprites&) = delete;

	PredefinedSprites& operator=(const PredefinedSprites&) = delete;

	static std::shared_ptr<Sprite> GetSprite(const std::wstring& spriteFullRelativePath) NOEXCEPT_WHEN_NDEBUG;

private:
	static std::vector<std::shared_ptr<Sprite>> m_sprites;
	static StaticConstructor m_constructor;

	static void Construct() noexcept;
};
