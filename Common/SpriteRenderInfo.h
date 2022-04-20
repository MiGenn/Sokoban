#pragma once
#include "IBinarySerializable.h"
#include "Sprite.h"
#include "Box2D.h"

class SpriteRenderInfo : public IBinarySerializable
{
public:
	SpriteRenderInfo() noexcept;
	SpriteRenderInfo(std::shared_ptr<Sprite> sprite, 
		Box2i boundingBox, float sizeInUnits, int layerIndex) NOEXCEPT_WHEN_NDEBUG;
	SpriteRenderInfo(const SpriteRenderInfo& spriteRenderInfo) noexcept;

	SpriteRenderInfo& operator=(const SpriteRenderInfo& right) noexcept;

	void SetPosition(Vector2i newPositionInUnits) noexcept;
	void SetBoundingBox(Box2i newBoundingBox) noexcept;
	void SetLayerIndex(int newLayerIndex) noexcept;
	bool IsEmptySprite() const noexcept;

	HBITMAP GetBitmap() const noexcept;
	Box2i GetBoundingBox() const noexcept;
	Vector2i GetPosition() const noexcept;
	float GetSizeInUnits() const noexcept;
	int GetLayerIndex() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	std::shared_ptr<Sprite> m_sprite;
	Box2i m_boundingBox;
	Vector2i m_positionInUnits;
	float m_sizeInUnits{ 0 };
	int m_layerIndex{ 0 };
};
