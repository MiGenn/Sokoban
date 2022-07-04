#include "RenderLayer.h"

#include <cassert>

RenderLayer::RenderLayer(HDC referenceContext, Vector2i size) NOEXCEPT_WHEN_NDEBUG
{
	Resize(referenceContext, size);
}

HDC RenderLayer::GetMemoryContext() noexcept
{
	m_isUsed = true;
	return m_context.Get();
}

Vector2i RenderLayer::GetSize() const noexcept
{
	return m_size;
}

bool RenderLayer::IsUsed() const noexcept
{
	return m_isUsed;
}

void RenderLayer::SetUsed(bool isUsed) noexcept
{
	m_isUsed = isUsed;
}

void RenderLayer::Resize(HDC referenceContext, Vector2i newSize) NOEXCEPT_WHEN_NDEBUG
{
	assert(newSize.x > 0 && newSize.y > 0);
	m_isUsed = false;
	m_size = newSize;
	m_bitmapSelectWrapper.Reset();

	m_context.Reset(CreateCompatibleDC(referenceContext));
	assert(m_context.Get());
	m_bitmap.reset(CreateCompatibleBitmap(referenceContext, newSize.x, newSize.y));
	m_bitmapSelectWrapper.Reset(m_context.Get(), m_bitmap.get());
}
