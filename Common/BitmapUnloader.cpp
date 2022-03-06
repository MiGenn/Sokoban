#include "BitmapUnloader.h"

#include "WinapiException.h"

void BitmapUnloader::operator()(void* resource) const
{
	DeleteObject(resource);
}
