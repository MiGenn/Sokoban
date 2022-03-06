#include "LevelLoader.h"

#include <fstream>
#include "TiledEntity.h"

void* LevelLoader::operator()(const std::wstring& relativeFullPath) const
{
    std::ifstream levelFile(relativeFullPath, std::ios::binary);
    Level* const level{ new Level() };

    while (!levelFile.eof())
    {
        int entitySize;
        levelFile.read(reinterpret_cast<char*>(&entitySize), sizeof(int));
        TiledEntity* entity{ reinterpret_cast<TiledEntity*>(new char[entitySize]) };
        levelFile.read(reinterpret_cast<char*>(entity), entitySize);

        int componentsCount;
        levelFile.read(reinterpret_cast<char*>(&componentsCount), sizeof(int));

        for (int i{ 0 }; i < componentsCount; ++i)
        {

        }

        //level->AddEntity(entity);
    }

    return level;
}
