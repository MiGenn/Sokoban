#include "BitmapUnloader.h"

#include "WinapiException.h"

void BitmapUnloader::operator()(void* resource) const
{
	if (!DeleteObject(resource))
		throw WINAPI_LAST_EXCEPTION();
}
