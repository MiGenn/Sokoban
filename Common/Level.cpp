#include "Level.h"

#include "VectorBinarySerializer.h"

const std::wstring Level::FolderRelativePath{ L"\\Content\\Levels\\" };
const std::wstring Level::FileExtension{ L".lvl" };

Level::Level(std::ifstream& file)
{
	DeserializeFromOpenedFileToSelf(file);	
}

TiledEntity& Level::operator[](int i)
{
	return *m_entities[i];
}

void Level::Add(std::unique_ptr<TiledEntity>&& entity)
{
	if (entity->GetTag() == TiledEntity::Tag::Character &&
		m_character != nullptr)
		return;

	if (!IsPlaceOccupied(*entity))
	{
		RecacheEntitiesWhenAdding(entity.get());
		m_entities.push_back(std::move(entity));
	}
}

void Level::Delete(const_iterator& entityIterator) noexcept
{
	auto entityPointer{ entityIterator->get() };
	if (entityPointer->GetTag() == TiledEntity::Tag::Character)
		return;

	RecacheEntitiesWhenDeleting(entityPointer);
	m_entities.erase(entityIterator);	
}

bool Level::IsPlaceOccupied(const TiledEntity& entity) const noexcept
{
	auto entityPosition{ entity.GetPosition() };
	auto entityLayerIndex{ entity.GetRenderInfo().GetLayerIndex() };
	auto entityIterator{ std::find_if(m_entities.begin(), m_entities.end(), 
		[entityPosition, entityLayerIndex](const std::unique_ptr<TiledEntity>& otherEntity)
		{
			return otherEntity->GetPosition() == entityPosition &&
				otherEntity->GetRenderInfo().GetLayerIndex() == entityLayerIndex;
		}) };

	if (entityIterator != m_entities.end())
		return true;

	return false;
}

std::vector<TiledEntity*> Level::FindByTag(TiledEntity::Tag tag) const noexcept
{
	std::vector<TiledEntity*> entities;
	std::for_each(m_entities.begin(), m_entities.end(),
		[&entities, tag](const std::unique_ptr<TiledEntity>& entity)
		{
			if (entity->GetTag() == tag)
				entities.push_back(entity.get());
		});

	return entities;
}

Level::const_iterator Level::FindEquivalent(const TiledEntity& entity) const noexcept
{
	return std::find_if(m_entities.begin(), m_entities.end(),
		[&entity](const std::unique_ptr<TiledEntity>& otherEntity)
		{
			return (*otherEntity) == entity;
		});
}

TiledEntity* Level::GetCharacter() noexcept
{
	return m_character;
}

std::vector<TiledEntity*>& Level::GetBarrels() noexcept
{
	return m_barrels;
}

std::vector<TiledEntity*>& Level::GetCrosses() noexcept
{
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
	CacheEntities();
}

Level::iterator Level::begin() noexcept
{
	return m_entities.begin();
}

Level::iterator Level::end() noexcept
{
	return m_entities.end();
}

Level::const_iterator Level::begin() const noexcept
{
	return m_entities.cbegin();
}

Level::const_iterator Level::end() const noexcept
{
	return m_entities.cend();
}

Level::const_iterator Level::cbegin() const noexcept
{
	return m_entities.cbegin();
}

Level::const_iterator Level::cend() const noexcept
{
	return m_entities.cend();
}

void Level::CacheEntities() const NOEXCEPT_WHEN_NDEBUG
{
	m_barrels = FindByTag(TiledEntity::Tag::Barrel);
	m_crosses = FindByTag(TiledEntity::Tag::Cross);
	assert(m_barrels.size() == m_crosses.size());
	auto character{ FindByTag(TiledEntity::Tag::Character) };
	assert(character.size() == 1);
	m_character = character[0];
}

void Level::RecacheEntitiesWhenAdding(TiledEntity* entity) const noexcept
{
	switch (entity->GetTag())
	{
	case TiledEntity::Tag::Barrel:
		m_barrels.push_back(entity);
		break;

	case TiledEntity::Tag::Cross:
		m_crosses.push_back(entity);
		break;

	case TiledEntity::Tag::Character:
		m_character = entity;
		break;
	}
}

void Level::RecacheEntitiesWhenDeleting(const TiledEntity* entity) const noexcept
{
	switch (entity->GetTag())
	{
	case TiledEntity::Tag::Barrel:
		EraseCashedPointer(entity, m_barrels);
		break;

	case TiledEntity::Tag::Cross:
		EraseCashedPointer(entity, m_crosses);
		break;
	}
}

void Level::EraseCashedPointer(const TiledEntity* entity, 
	std::vector<TiledEntity*>& cashedEntities) const noexcept
{
	cashedEntities.erase(std::find_if(cashedEntities.begin(), cashedEntities.end(),
		[entity](const TiledEntity* cashedEntity)
		{
			return cashedEntity == entity;
		}));
}
