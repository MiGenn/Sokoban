#include <fstream>
#include "LevelSaver.h"
#include "TiledEntity.h"
#include "LevelSaver.h"

void LevelSaver::Save(const Level& level, std::string name)
{
    std::ofstream levelFile(Level::LevelFolderRelativePath + name + Level::LevelFileExtension, std::ios::binary);

    for (auto& entity : level.entities)
    {
        const int entitySize{ sizeof(entity) };
        levelFile.write(reinterpret_cast<const char*>(&entitySize), sizeof(int));
        levelFile.write(reinterpret_cast<const char*>(&entity), entitySize);
    }
}
