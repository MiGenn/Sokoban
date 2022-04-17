#pragma once
#include <string>
#include <array>
#include "BuildInfo.h"
#include "Character.h"

class Level final : public IBinarySerializable
{
public:
	using iterator = std::vector<std::unique_ptr<TiledEntity>>::iterator;
	using const_iterator = std::vector<std::unique_ptr<TiledEntity>>::const_iterator;

	static const std::wstring FolderRelativePath;
	static const std::wstring FileExtension;

	Level() noexcept = default;
	Level(std::ifstream& file);
	Level(const Level&) = delete;

	Level& operator=(const Level&) = delete;
	TiledEntity& operator[](int i);

	void Add(std::unique_ptr<TiledEntity>&& entity);
	void Delete(const_iterator& entity) noexcept;

	bool IsPlaceOccupied(const TiledEntity& entity) const noexcept;
	std::vector<TiledEntity*> FindByTag(TiledEntity::Tag tag) const noexcept;
	const_iterator FindEquivalent(const TiledEntity& entity) const noexcept;

	TiledEntity* GetCharacter() noexcept;
	std::vector<TiledEntity*>& GetBarrels() noexcept;
	std::vector<TiledEntity*>& GetCrosses() noexcept;
	int GetEntitiesCount() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

	iterator begin() noexcept;
	iterator end() noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;

private:
	std::vector<std::unique_ptr<TiledEntity>> m_entities;

	mutable TiledEntity* m_character = nullptr;
	mutable std::vector<TiledEntity*> m_barrels;
	mutable std::vector<TiledEntity*> m_crosses;

	void CacheEntities() const NOEXCEPT_WHEN_NDEBUG;
	void RecacheEntitiesWhenAdding(TiledEntity* entity) const noexcept;
	void RecacheEntitiesWhenDeleting(const TiledEntity* entity) const noexcept;

	void EraseCashedPointer(const TiledEntity* entity, 
		std::vector<TiledEntity*>& cashedEntities) const noexcept;
};
