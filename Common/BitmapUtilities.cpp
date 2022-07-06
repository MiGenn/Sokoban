#include "BitmapUtilities.h"

HBITMAP Utilities::Winapi::Bitmap::LoadBMP(const std::wstring& fullPath)
{
    HANDLE bitmap{ LoadImage(nullptr, fullPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE) };
    if (!bitmap)
        throw WINAPI_LAST_EXCEPTION();

    return static_cast<HBITMAP>(bitmap);
}

void Utilities::Winapi::Bitmap::UnloadBMP(HBITMAP sprite)
{
    if (!DeleteObject(sprite))
        throw WINAPI_LAST_EXCEPTION();
}
 