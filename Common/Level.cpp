#include "Level.h"

const std::string Level::LevelFolderRelativePath{ "\\Content\\Levels\\" };
const std::string Level::LevelFileExtension{ ".lvl" };

Level::Level() :
	characterPointer(new Character({ ResourceManager::GetBitmapInterface(L"Content\\Textures\\GameObjects\\", L"Character.bmp"),
		{ { 0, 0 }, { 24, 24 } }, 1 }))
{
	entities.push_back(characterPointer);
}

void Level::AddBarrel(TiledEntity* barrel)
{
	entities.push_back(barrel);
	barrelsPointers.push_back(barrel);
}

void Level::AddCross(TiledEntity* cross)
{
	entities.push_back(cross);
	crossesPointers.push_back(cross);
}

void Level::RemoveBarrel(TiledEntity* barrel)
{
	RemoveEntity(barrel);

	auto barrelIterator{ std::find_if(barrelsPointers.begin(), barrelsPointers.end(), [barrel](TiledEntity* otherBarrel)
		{
			return barrel == otherBarrel;
		}) };
	barrelsPointers.erase(barrelIterator);
}

void Level::RemoveCross(TiledEntity* cross)
{
	RemoveEntity(cross);

	auto barrelIterator{ std::find_if(crossesPointers.begin(), crossesPointers.end(), [cross](TiledEntity* otherCross)
		{
			return cross == otherCross;
		}) };
	crossesPointers.erase(barrelIterator);
}

void Level::RemoveEntity(TiledEntity* entity)
{
	auto barrelIterator{ std::find_if(entities.begin(), entities.end(), [entity](TiledEntity* otherEntity)
	{
		return entity == otherEntity;
	}) };
	entities.erase(barrelIterator);
}
