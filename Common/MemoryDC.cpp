#include "MemoryDC.h"

Utilities::Winapi::SmartPointer::MemoryDC::MemoryDC(HDC memoryContext) noexcept :
	m_memoryContext(memoryContext)
{
	
}

Utilities::Winapi::SmartPointer::MemoryDC::~MemoryDC() noexcept
{
	if (m_memoryContext)
		DeleteDC(m_memoryContext);
}

HDC Utilities::Winapi::SmartPointer::MemoryDC::Get() const noexcept
{
	return m_memoryContext;
}

void Utilities::Winapi::SmartPointer::MemoryDC::Reset(HDC memoryContext) noexcept
{
	this->~MemoryDC();
	m_memoryContext = memoryContext;
}
