#pragma once
#include "Loader.h"

class BitmapLoader final : public Loader
{
public:
	void* operator()(const std::wstring& relativeFullPath) const override;
};
