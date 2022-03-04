#include "BitmapLoader.h"

void* BitmapLoader::operator()(const std::wstring& relativeFullPath) const 
{
    auto bitmap{ LoadImage(NULL, relativeFullPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE) };
    if (!bitmap)
        throw LAST_EXCEPTION();

    return bitmap;
}
