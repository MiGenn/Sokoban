#pragma once
#include "Level.h"
#include "Loader.h"

class LevelLoader final : public Loader
{
public:
	void* operator()(const std::wstring& relativeFullPath) const override;
};
