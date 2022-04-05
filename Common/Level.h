#pragma once
#include <string>
#include <array>
#include "BuildInfo.h"
#include "Character.h"

class Level final : public IBinarySerializable
{
public:
	static const std::string LevelFolderRelativePath;
	static const std::string LevelFileExtension;

	Level() noexcept;
	Level(std::ifstream& file);
	Level(const Level&) = delete;

	Level& operator=(const Level&) = delete;
	TiledEntity& operator[](int i);

	void BinarySerializeToOpenedFile(std::ofstream& file) const override;
	void BinaryDeserializeFromOpenedFileToSelf(std::ifstream& file) override;

	Character& GetCharacter() const NOEXCEPT_WHEN_NDEBUG;
	std::vector<TiledEntity*>& GetBarrels() const NOEXCEPT_WHEN_NDEBUG;
	int GetEntitiesCount() const noexcept;

	constexpr auto begin() noexcept;
	constexpr auto end() noexcept;

private:
	std::vector<std::unique_ptr<TiledEntity>> m_entities;

	Character* mutable m_character = nullptr;
	std::vector<TiledEntity*> m_barrels;
	std::vector<TiledEntity*> m_crosses;
};
