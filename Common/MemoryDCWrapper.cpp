#include "MemoryDCWrapper.h"

MemoryDCWrapper::MemoryDCWrapper(HDC memoryContext) noexcept :
	m_memoryContext(memoryContext)
{
	
}

MemoryDCWrapper::~MemoryDCWrapper() noexcept
{
	if (m_memoryContext != NULL)
		DeleteDC(m_memoryContext);
}

HDC MemoryDCWrapper::Get() const noexcept
{
	return m_memoryContext;
}

void MemoryDCWrapper::Reset(HDC memoryContext) noexcept
{
	this->~MemoryDCWrapper();
	m_memoryContext = memoryContext;
}
