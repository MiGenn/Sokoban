#include "TiledEntityFactory.h"

TiledEntity* TiledEntityFactory::CreateWall(Vector2i position)
{
	TileRenderInfo renderInfo{ 
		ResourceManager::GetBitmapInterface(L"Content\\Textures\\GameObjects\\", L"Wall.bmp"), 
		{ { 0, 0 }, { 24,24 } }, 0};

	TiledEntity* wall{ new TiledEntity(renderInfo, position, true, false) };

	return wall;
}

TiledEntity* TiledEntityFactory::CreateRoad(Vector2i position)
{
	TileRenderInfo renderInfo{
	ResourceManager::GetBitmapInterface(L"Content\\Textures\\GameObjects\\", L"Road.bmp"),
	{ { 0, 0 }, { 24,24 } }, 0 };

	TiledEntity* Road{ new TiledEntity(renderInfo, position, false, false) };

	return Road;
}

TiledEntity* TiledEntityFactory::CreateBarrel(Vector2i position)
{
	TileRenderInfo renderInfo{
	ResourceManager::GetBitmapInterface(L"Content\\Textures\\GameObjects\\", L"Barrel.bmp"),
	{ { 0, 0 }, { 24,24 } }, 0 };

	TiledEntity* Barrel{ new TiledEntity(renderInfo, position, true, true) };

	return Barrel;
}

TiledEntity* TiledEntityFactory::CreateCross(Vector2i position)
{
	TileRenderInfo renderInfo{
	ResourceManager::GetBitmapInterface(L"Content\\Textures\\GameObjects\\", L"Cross.bmp"),
	{ { 0, 0 }, { 24,24 } }, 0 };

	TiledEntity* Cross{ new TiledEntity(renderInfo, position, false, false) };

	return Cross;
}
