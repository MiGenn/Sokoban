#pragma once
#include "SpriteRenderInfo.h"

class TiledEntity final : public IBinarySerializable
{
public:
	enum class Tag : char
	{
		Unknown,
		Wall,
		Road,
		Box,
		Point,
		Character
	};

	TiledEntity() noexcept = default;
	TiledEntity(std::ifstream& file);
	TiledEntity(const SpriteRenderInfo& renderInfo, Tag tag) noexcept;
	TiledEntity(const SpriteRenderInfo& renderInfo, Tag tag, Vector2f position) noexcept;
	TiledEntity(const TiledEntity& entity) noexcept;
	~TiledEntity() noexcept = default;

	TiledEntity& operator=(const TiledEntity& right) noexcept;
	bool operator==(const TiledEntity& right) noexcept;

	bool IsCollision(const TiledEntity& otherEntity) const noexcept;
	bool IsInTheSamePosition(const TiledEntity& otherEntity) const noexcept;

	void Move(Vector2f translation) noexcept;
	void SetPosition(Vector2f newPosition) noexcept;

	Vector2f GetPosition() const noexcept;
	Tag GetTag() const noexcept;
	const SpriteRenderInfo& GetRenderInfo() const noexcept;

	void SerializeIDToOpenedFile(std::ofstream& file) const override;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	Vector2f m_position;
	Tag m_tag{ Tag::Unknown };
	mutable SpriteRenderInfo m_renderInfo;
};
