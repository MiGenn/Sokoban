#pragma once
#include "IBinarySerializable.h"
#include "Sprite.h"
#include "Box2D.h"

class SpriteRenderInfo : public IBinarySerializable
{
public:
	SpriteRenderInfo() noexcept = default;
	SpriteRenderInfo(std::shared_ptr<Sprite> sprite, Vector2i position,
		Box2i boundingBox, int layerIndex) NOEXCEPT_WHEN_NDEBUG;
	SpriteRenderInfo(const SpriteRenderInfo& spriteRenderInfo) noexcept;

	SpriteRenderInfo& operator=(const SpriteRenderInfo& right) noexcept;

	void SetPosition(Vector2i newPosition) noexcept;
	void SetBoundingBox(Box2i newBoundingBox) noexcept;
	void SetLayerIndex(int newLayerIndex) noexcept;
	bool IsEmptySprite() const noexcept;

	HBITMAP GetBitmap() const noexcept;
	Box2i GetBoundingBox() const noexcept;
	Vector2i GetWorldPosition() const noexcept;
	int GetLayerIndex() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	std::shared_ptr<Sprite> m_sprite{ nullptr };
	Box2i m_boundingBox;
	Vector2i m_worldPosition;
	int m_layerIndex = 0;
};
