#pragma once
#include <string>
#include "Character.h"

class Level final
{
public:
	static const std::string LevelFolderRelativePath;
	static const std::string LevelFileExtension;

	std::vector<TiledEntity*> entities;

	Character* characterPointer;
	std::vector<TiledEntity*> crossesPointers;
	std::vector<TiledEntity*> barrelsPointers;

	Level();
	Level(const Level&) = delete;

	Level& operator=(const Level&) = delete;

	void AddBarrel(TiledEntity* barrel);
	void AddCross(TiledEntity* cross);

	void RemoveBarrel(TiledEntity* barrel);
	void RemoveCross(TiledEntity* cross);
	void RemoveEntity(TiledEntity* entity);
};
