#pragma once
#include <memory>
#include <string>
#include <vector>
#include "StaticConstuctor.h"
#include "Sprite.h"
#include "Box2D.h"
#include "BuildInfo.h"

class PredefinedSprites
{
public:
	static constexpr int tileSizeInPixels{ 64 };
	static const std::wstring tileSetRelativeFullPath;

	static const Box2i wallBoundingBox;
	static const Box2i roadBoundingBox;
	static const Box2i boxBoundingBox;
	static const Box2i pointBoundingBox;
	static const Box2i characterBoundingBox;

	PredefinedSprites() = delete;
	PredefinedSprites(const PredefinedSprites&) = delete;

	PredefinedSprites& operator=(const PredefinedSprites&) = delete;

	static std::shared_ptr<Sprite> GetSprite(const std::wstring& relativeFullPath) NOEXCEPT_WHEN_NDEBUG;

private:
	static std::vector<std::shared_ptr<Sprite>> m_sprites;
	static Utilities::Cpp::StaticConstructor m_constructor;

	static void Construct() noexcept;
};
