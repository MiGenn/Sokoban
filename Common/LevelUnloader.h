#pragma once
#include "Level.h"
#include "Unloader.h"

class LevelUnloader : public Unloader
{
public:
	void operator()(void* resource) const override;
};
