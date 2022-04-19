#pragma once
#include "WinapiException.h"

class MemoryDCWrapper final
{
public:
	MemoryDCWrapper() noexcept = default;
	MemoryDCWrapper(HDC memoryContext) noexcept;
	MemoryDCWrapper(const MemoryDCWrapper&) = delete;
	~MemoryDCWrapper() noexcept;

	MemoryDCWrapper& operator=(const MemoryDCWrapper&) = delete;

	HDC Get() const noexcept;
	void Reset(HDC memoryContext) noexcept;

private:
	HDC m_memoryContext{ NULL };
};
