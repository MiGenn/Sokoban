#include "Level.h"

#include <algorithm>
#include "VectorBinarySerializer.h"

const std::string Level::LevelFolderRelativePath{ "\\Content\\Levels\\" };
const std::string Level::LevelFileExtension{ ".lvl" };

Level::Level(std::ifstream& file)
{
	DeserializeFromOpenedFileToSelf(file);
	GetCharacter();
	GetBarrels();
	GetCrosses();
}

TiledEntity& Level::operator[](int i)
{
	return *m_entities[i];
}

void Level::AddEntity(std::unique_ptr<TiledEntity>&& entity)
{
	m_entities.emplace_back(std::move(entity));
}

void Level::DeleteEntity(iterator& entity) NOEXCEPT_WHEN_NDEBUG
{

}

void Level::DeleteEntity(const TiledEntity& entity) NOEXCEPT_WHEN_NDEBUG
{
	auto entityIterator{ std::find_if(begin(), end(), [&entity](const std::unique_ptr<TiledEntity>& otherEntity)
		{
			return entity == (*otherEntity);
		}) };

	assert(entityIterator != end());

	m_entities.erase(entityIterator);
} 

TiledEntity& Level::GetCharacter() NOEXCEPT_WHEN_NDEBUG
{
	if (!m_character)
		for (auto& entity : m_entities)
			if (entity->GetTag() == TiledEntity::Tag::Character)
				m_character = entity.get();

	assert(m_character != nullptr);

	return *m_character;
}

std::vector<TiledEntity*>& Level::GetBarrels() NOEXCEPT_WHEN_NDEBUG
{
	if (m_barrels.empty())
		for (auto& entity : m_entities)
			if (entity->GetTag() == TiledEntity::Tag::Barrel)
				m_barrels.push_back(entity.get());

	assert(m_barrels.size() != 0);

	return m_barrels;
}

std::vector<TiledEntity*>& Level::GetCrosses() NOEXCEPT_WHEN_NDEBUG
{
	if (m_barrels.empty())
		for (auto& entity : m_entities)
			if (entity->GetTag() == TiledEntity::Tag::Cross)
				m_crosses.push_back(entity.get());

	assert(m_crosses.size() != 0);

	return m_crosses;
}

int Level::GetEntitiesCount() const noexcept
{
	return (int)m_entities.size();
}

void Level::SerializeToOpenedFile(std::ofstream& file) const
{
	VectorBinarySerializer::SerializeToOpenedFile(m_entities, file);
}

void Level::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	VectorBinarySerializer::DeserializeFromOpenedFile(m_entities, file);
}

Level::iterator Level::begin() noexcept
{
	return m_entities.begin();
}

Level::iterator Level::end() noexcept
{
	return m_entities.end();
}
