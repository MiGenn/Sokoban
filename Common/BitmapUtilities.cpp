#include "BitmapUtilities.h"

HBITMAP BitmapUtilities::LoadBMP(const std::wstring& relativeFullPath)
{
    HANDLE bitmap{ LoadImage(NULL, relativeFullPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE) };
    if (!bitmap)
        throw WINAPI_LAST_EXCEPTION();

    return static_cast<HBITMAP>(bitmap);
}

void BitmapUtilities::UnloadBMP(HBITMAP sprite)
{
    if (!DeleteObject(sprite))
        throw WINAPI_LAST_EXCEPTION();
}
 