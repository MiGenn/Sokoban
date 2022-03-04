#pragma once

class Unloader
{
public:
	virtual void operator()(void* resource) const = 0;
};
