#pragma once
#include "Unloader.h"

class BitmapUnloader final : public Unloader
{
public:
	void operator()(void* resource) const override;
};
