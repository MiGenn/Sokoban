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

	static const std::string LevelFolderRelativePath;
	static const std::string LevelFileExtension;

	Level() noexcept = default;
	Level(std::ifstream& file);
	Level(const Level&) = delete;

	Level& operator=(const Level&) = delete;
	TiledEntity& operator[](int i);

	void AddEntity(std::unique_ptr<TiledEntity>&& entity);
	void DeleteEntity(const TiledEntity& entity) NOEXCEPT_WHEN_NDEBUG;
	void DeleteEntity(iterator& entity) NOEXCEPT_WHEN_NDEBUG;

	TiledEntity& GetCharacter() NOEXCEPT_WHEN_NDEBUG;
	std::vector<TiledEntity*>& GetBarrels() NOEXCEPT_WHEN_NDEBUG;
	std::vector<TiledEntity*>& GetCrosses() NOEXCEPT_WHEN_NDEBUG;
	int GetEntitiesCount() const noexcept;

	void SerializeToOpenedFile(std::ofstream& file) const override;
	void DeserializeFromOpenedFileToSelf(std::ifstream& file) override;

	iterator begin() noexcept;
	iterator end() noexcept;

private:
	std::vector<std::unique_ptr<TiledEntity>> m_entities;

	TiledEntity* m_character = nullptr;
	std::vector<TiledEntity*> m_barrels;
	std::vector<TiledEntity*> m_crosses;
};
