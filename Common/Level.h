#pragma once
#include <string>
#include "Character.h"

class Level final
{
public:
	static const std::string LevelFolderRelativePath;
	static const std::string LevelFileExtension;

	Character* character;
	std::vector<TiledEntity*> entities;

	Level();
	Level(const Level&) = delete;

	Level& operator=(const Level&) = delete;
};
