#include "BitmapUnloader.h"

void BitmapUnloader::operator()(void* resource) const
{
	DeleteObject(resource);
}
