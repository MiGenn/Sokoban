#include "Level.h"

#include "VectorBinarySerializer.h"
#include "VectorUtilities.h"

const std::wstring Level::levelsFolderRelativePath{ L"\\Content\\Levels\\" };
const std::wstring Level::fileExtension{ L".lvl" };

Level::Level(std::ifstream& file)
{
	DeserializeFromOpenedFileToSelf(file);	
}

Level::Level(const Level& level)
{
	(*this) = level;
}

Level& Level::operator=(const Level& right)
{
	m_entities = Utilities::Cpp::Container::Duplicate(right.m_entities);
	CacheEntities();

	return *this;
}

TiledEntity& Level::operator[](int i)
{
	return *m_entities[i];
}

bool Level::Add(std::unique_ptr<TiledEntity>&& entity) noexcept
{
	if (entity->GetTag() == TiledEntity::Tag::Character && m_cachedCharacterPointer)
		return false;

	if (IsPlaceOccupied(*entity))
		return false;

	RecacheEntitiesWhenAdding(entity.get());
	m_entities.push_back(std::move(entity));

	return true;
}

bool Level::Delete(const_iterator& entityIterator) noexcept
{
	auto entity{ entityIterator->get() };
	if (entity->GetTag() == TiledEntity::Tag::Character)
		return false;

	RecacheEntitiesWhenDeleting(entity);
	m_entities.erase(entityIterator);	

	return true;
}

bool Level::CanEntityBeOverlapped(const TiledEntity& entity) noexcept
{
	switch (entity.GetTag())
	{
	case TiledEntity::Tag::Road:
	case TiledEntity::Tag::Point:
		return true;
	}

	return false;
}

bool Level::CanEntitiesBeInTheSamePosition(const TiledEntity& entity, const TiledEntity& otherEntity) noexcept
{
	if (otherEntity.GetRenderInfo().GetLayerIndex() == entity.GetRenderInfo().GetLayerIndex())
		return false;

	return CanEntityBeOverlapped(otherEntity) || CanEntityBeOverlapped(entity);;
}

bool Level::IsPlaceOccupied(const TiledEntity& entity) const noexcept
{
	auto entityIterator{ std::find_if(m_entities.begin(), m_entities.end(),
		[&entity](const std::unique_ptr<TiledEntity>& otherEntity)
		{
			if (otherEntity->IsCollision(entity))
				return !CanEntitiesBeInTheSamePosition(entity, *otherEntity);

			return false;
		}) };

	if (entityIterator == m_entities.end())
		return false;

	return true;
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
			return otherEntity->IsInTheSamePosition(entity) &&
				otherEntity->GetTag() == entity.GetTag() &&
				otherEntity->GetRenderInfo().GetBitmap() == entity.GetRenderInfo().GetBitmap();
		});
}

TiledEntity* Level::GetCharacter() noexcept
{
	return m_cachedCharacterPointer;
}

std::vector<TiledEntity*>& Level::GetBoxes() noexcept
{
	return m_cachedBoxPointers;
}

std::vector<TiledEntity*>& Level::GetPointes() noexcept
{
	return m_cachedPointPointers;
}

size_t Level::GetEntitiesCount() const noexcept
{
	return m_entities.size();
}

void Level::SerializeIDToOpenedFile(std::ofstream& file) const
{
	IBinarySerializable::SerializeIDToOpenedFile<Level>(file);
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
	m_cachedBoxPointers = FindByTag(TiledEntity::Tag::Box);
	m_cachedPointPointers = FindByTag(TiledEntity::Tag::Point);
	assert(m_cachedBoxPointers.size() == m_cachedPointPointers.size());
	auto characters{ FindByTag(TiledEntity::Tag::Character) };
	assert(characters.size() == 1);
	m_cachedCharacterPointer = characters[0];
}

bool Level::IsWallOrBox(TiledEntity::Tag tag)
{
	return tag == TiledEntity::Tag::Wall ||
		tag == TiledEntity::Tag::Box;
}

void Level::RecacheEntitiesWhenAdding(TiledEntity* entity) const noexcept
{
	switch (entity->GetTag())
	{
	case TiledEntity::Tag::Box:
		m_cachedBoxPointers.push_back(entity);
		break;

	case TiledEntity::Tag::Point:
		m_cachedPointPointers.push_back(entity);
		break;

	case TiledEntity::Tag::Character:
		m_cachedCharacterPointer = entity;
		break;
	}
}

void Level::RecacheEntitiesWhenDeleting(const TiledEntity* entity) const noexcept
{
	switch (entity->GetTag())
	{
	case TiledEntity::Tag::Box:
		EraseCachedPointer(entity, m_cachedBoxPointers);
		break;

	case TiledEntity::Tag::Point:
		EraseCachedPointer(entity, m_cachedPointPointers);
		break;
	}
}

void Level::EraseCachedPointer(const TiledEntity* entity, 
	std::vector<TiledEntity*>& cachedEntityPointers) const noexcept
{
	cachedEntityPointers.erase(std::find_if(cachedEntityPointers.begin(), cachedEntityPointers.end(),
		[entity](const TiledEntity* cashedEntity)
		{
			return cashedEntity == entity;
		}));
}
