#pragma once
#include "SpriteRenderInfo.h"

class TiledEntity : public IBinarySerializable
{
public:
	static const int tileSize{ 24 };

	//TiledEntity(std::ifstream& file);
	TiledEntity(const SpriteRenderInfo& renderInfo,
		Vector2i position, bool isCollidable, bool isMovable);

	bool operator==(const TiledEntity& otherEntity);
	bool operator!=(const TiledEntity& otherEntity);

	void SetPosition(Vector2i newPosition);
	const SpriteRenderInfo& GetRenderInfo() const;
	Vector2i GetPosition() const; 
	bool IsCollision(const TiledEntity& otherTiledEntity) const;
	virtual void Move(Vector2i translation);

	bool IsCollidable() const;
	bool IsMovable() const;

	void BinarySerializeToOpenedFile(std::ofstream& file) const override;
	void BinaryDeserializeFromOpenedFileToSelf(std::ifstream& file) override;

private:
	Vector2i m_position;
	mutable SpriteRenderInfo m_renderInfo;

	bool m_isCollidable = false;
	bool m_isMovable = false;
};
