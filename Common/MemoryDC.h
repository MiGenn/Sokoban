#pragma once
#include "WinapiException.h"

namespace Utilities::Winapi::SmartPointer
{
	class MemoryDC final
	{
	public:
		MemoryDC() noexcept = default;
		MemoryDC(HDC memoryContext) noexcept;
		MemoryDC(const MemoryDC&) = delete;
		~MemoryDC() noexcept;

		MemoryDC& operator=(const MemoryDC&) = delete;

		HDC Get() const noexcept;
		void Reset(HDC memoryContext) noexcept;

	private:
		HDC m_memoryContext{ nullptr };
	};
}
