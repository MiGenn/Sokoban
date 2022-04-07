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
	TiledEntity(SpriteRenderInfo&& renderInfo, Tag tag);
	TiledEntity(SpriteRenderInfo&& renderInfo, Tag tag, Vector2i position);
	TiledEntity(const TiledEntity&) = delete;
	~TiledEntity() noexcept = default;

	TiledEntity& operator=(const TiledEntity&) = delete;
	bool operator==(const TiledEntity& right) noexcept;
	bool operator!=(const TiledEntity& right) noexcept;

	void Move(Vector2i translation) noexcept;
	bool IsCollision(const TiledEntity& otherTiledEntity) const noexcept;
	void SetPosition(Vector2i newPosition) noexcept;

	Vector2i GetPosition() const noexcept;
	Tag GetTag() const noexcept;
	const SpriteRenderInfo& GetRenderInfo() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

	//
	constexpr bool IsRegistred() const noexcept;

private:
	Vector2i m_position;
	Tag m_tag{ Tag::Unknown };
	mutable SpriteRenderInfo m_renderInfo;
};

constexpr bool TiledEntity::IsRegistred() const noexcept
{
	return true;
}
