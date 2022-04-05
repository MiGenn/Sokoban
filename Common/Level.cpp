#include "Level.h"

#include "VectorBinarySerializer.h"

const std::string Level::LevelFolderRelativePath{ "\\Content\\Levels\\" };
const std::string Level::LevelFileExtension{ ".lvl" };

Level::Level()
{
	
}

Level::Level(std::ifstream& file)
{
	BinaryDeserializeFromOpenedFileToSelf(file);
	m_character = &GetCharacter();
}

TiledEntity& Level::operator[](int i)
{
	return *m_entities[i];
}

void Level::BinarySerializeToOpenedFile(std::ofstream& file) const
{
	VectorBinarySerializer::SerializeToOpenedFile(m_entities, file);
}

void Level::BinaryDeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	VectorBinarySerializer::DeserializeFromOpenedFile(m_entities, file);
}

Character& Level::GetCharacter() const NOEXCEPT_WHEN_NDEBUG
{
	if (!m_character)
		for (auto& entity : m_entities)
			dynamic_cast<Character*>(entity.get());

	assert(m_character != nullptr);

	return *m_character;
}

int Level::GetEntitiesCount() const noexcept
{
	return m_entities.size();
}

constexpr auto Level::begin() noexcept
{
	return m_entities.begin();
}

constexpr auto Level::end() noexcept
{
	return m_entities.end();
}
