#pragma once
#include "string"

class Loader
{
public:
	virtual void* operator()(const std::wstring& relativeFullPath) const = 0;
};
