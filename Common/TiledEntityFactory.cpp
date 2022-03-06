#include "TiledEntityFactory.h"

TiledEntity* TiledEntityFactory::CreateWall()
{
	TileRenderInfo renderInfo{ 
		ResourceManager::GetBitmapInterface(L"Content\\Textures\\GameObjects\\", L"Wall.bmp"), 
		{ { 0, 0 }, { 24,24 } }, 0};

	TiledEntity* wall{ new TiledEntity(renderInfo, { 0,0 }, true, false) };

	return wall;
}

TiledEntity* TiledEntityFactory::CreateRoad()
{
	TileRenderInfo renderInfo{
	ResourceManager::GetBitmapInterface(L"Content\\Textures\\GameObjects\\", L"Road.bmp"),
	{ { 0, 0 }, { 24,24 } }, 0 };

	TiledEntity* Road{ new TiledEntity(renderInfo, { 0,0 }, false, false) };

	return Road;
}

TiledEntity* TiledEntityFactory::CreateBarrel()
{
	TileRenderInfo renderInfo{
	ResourceManager::GetBitmapInterface(L"Content\\Textures\\GameObjects\\", L"Barrel.bmp"),
	{ { 0, 0 }, { 24,24 } }, 0 };

	TiledEntity* Barrel{ new TiledEntity(renderInfo, { 0,0 }, true, true) };

	return Barrel;
}

TiledEntity* TiledEntityFactory::CreateCross()
{
	TileRenderInfo renderInfo{
	ResourceManager::GetBitmapInterface(L"Content\\Textures\\GameObjects\\", L"Cross.bmp"),
	{ { 0, 0 }, { 24,24 } }, 0 };

	TiledEntity* Cross{ new TiledEntity(renderInfo, { 0,0 }, false, false) };

	return Cross;
}
