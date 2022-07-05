#pragma once
#include <string>
#include <array>
#include "TiledEntity.h"
#include "BuildInfo.h"

class Level final : public IBinarySerializable
{
public:
	using iterator = std::vector<std::unique_ptr<TiledEntity>>::iterator;
	using const_iterator = std::vector<std::unique_ptr<TiledEntity>>::const_iterator;

	static const std::wstring levelsFolderRelativePath;
	static const std::wstring fileExtension;

	Level() noexcept = default;
	Level(std::ifstream& file);
	Level(const Level& level);

	Level& operator=(const Level& right);
	TiledEntity& operator[](int i);

	bool Add(std::unique_ptr<TiledEntity>&& entity) noexcept;
	bool Delete(const_iterator& entity) noexcept;

	static bool CanEntityBeOverlapped(const TiledEntity& entity) noexcept;
	static bool CanEntitiesBeInTheSamePosition(const TiledEntity& entity, const TiledEntity& otherEntity) noexcept;
	bool IsPlaceOccupied(const TiledEntity& entity) const noexcept;
	std::vector<TiledEntity*> FindByTag(TiledEntity::Tag tag) const noexcept;
	const_iterator FindEquivalent(const TiledEntity& entity) const noexcept;

	TiledEntity* GetCharacter() noexcept;
	std::vector<TiledEntity*>& GetBoxes() noexcept;
	std::vector<TiledEntity*>& GetPointes() noexcept;
	size_t GetEntitiesCount() const noexcept;

	void SerializeIDToOpenedFile(std::ofstream& file) const override;

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

	mutable TiledEntity* m_cachedCharacterPointer{ nullptr };
	mutable std::vector<TiledEntity*> m_cachedBoxPointers;
	mutable std::vector<TiledEntity*> m_cachedPointPointers;

	static bool IsWallOrBox(TiledEntity::Tag tag);

	void CacheEntities() const NOEXCEPT_WHEN_NDEBUG;
	void RecacheEntitiesWhenAdding(TiledEntity* entity) const noexcept;
	void RecacheEntitiesWhenDeleting(const TiledEntity* entity) const noexcept;

	void EraseCachedPointer(const TiledEntity* entity, 
		std::vector<TiledEntity*>& cachedEntities) const noexcept;
};
