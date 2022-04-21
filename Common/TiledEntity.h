#pragma once
#include "SpriteRenderInfo.h"

class TiledEntity : public IBinarySerializable
{
public:
	enum class Tag : char
	{
		Unknown,
		Wall,
		Road,
		Cross,
		Barrel,
		Character
	};

	static constexpr int tileSize{ 24 };

	TiledEntity() noexcept = default;
	TiledEntity(std::ifstream& file);
	TiledEntity(const SpriteRenderInfo& renderInfo, Tag tag);
	TiledEntity(const SpriteRenderInfo& renderInfo, Tag tag, Vector2i positionInUnits);
	TiledEntity(const TiledEntity& entity);
	~TiledEntity() noexcept = default;

	TiledEntity& operator=(const TiledEntity& right);
	bool operator==(const TiledEntity& right) noexcept;
	bool operator!=(const TiledEntity& right) noexcept;

	void Move(Vector2i translation) noexcept;
	void SetPosition(Vector2f newPositionInUnits) noexcept;

	Vector2f GetPosition() const noexcept;
	Tag GetTag() const noexcept;
	const SpriteRenderInfo& GetRenderInfo() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

	constexpr bool IsRegistred() const noexcept override;

private:
	Vector2f m_positionInUnits;
	Tag m_tag{ Tag::Unknown };
	mutable SpriteRenderInfo m_renderInfo;
};

constexpr bool TiledEntity::IsRegistred() const noexcept
{
	return true;
}
