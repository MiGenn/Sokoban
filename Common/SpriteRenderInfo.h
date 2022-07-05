#pragma once
#include "IBinarySerializable.h"
#include "Sprite.h"
#include "Box2D.h"

class SpriteRenderInfo : public IBinarySerializable
{
public:
	SpriteRenderInfo() noexcept = default;
	SpriteRenderInfo(std::shared_ptr<Sprite> sprite, const Box2i& boundingBox, int layerIndex,
		bool isPreservingAspectRatio = true, Vector2f size = Vector2f(1.f, 1.f)) NOEXCEPT_WHEN_NDEBUG;
	SpriteRenderInfo(const SpriteRenderInfo& spriteRenderInfo) noexcept;

	SpriteRenderInfo& operator=(const SpriteRenderInfo& right) noexcept;

	void SetPosition(Vector2f newPosition) noexcept;
	void SetBoundingBox(Box2i newBoundingBox) noexcept;
	void SetSize(Vector2f newSize) noexcept;
	void SetLayerIndex(int newLayerIndex) noexcept;
	bool IsEmptySprite() const noexcept;

	HBITMAP GetBitmap() const noexcept;
	Box2i GetBoundingBox() const noexcept;
	Vector2f GetPosition() const noexcept;
	Vector2f GetSize() const noexcept;
	bool IsPreservingAspectRatio() const noexcept;
	int GetLayerIndex() const noexcept;

	void SerializeIDToOpenedFile(std::ofstream& file) const override;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	std::shared_ptr<Sprite> m_sprite{ std::make_shared<Sprite>() };
	Box2i m_boundingBox;
	Vector2f m_position;
	Vector2f m_size;
	bool m_isPreservingAspectRatio;
	int m_layerIndex{ 0 };
};
