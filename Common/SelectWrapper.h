#pragma once
#include "WinapiException.h"

class SelectWrapper final
{
public:
	SelectWrapper() noexcept = default;
	SelectWrapper(HDC context, HGDIOBJ object) noexcept;
	SelectWrapper(const SelectWrapper&) = delete;
	~SelectWrapper() noexcept;

	SelectWrapper& operator=(const SelectWrapper&) = delete;

	void Reset(HDC context = NULL, HGDIOBJ object = NULL) noexcept;

private:
	HDC m_context{ NULL };
	HGDIOBJ m_previousObject{ NULL };
};
