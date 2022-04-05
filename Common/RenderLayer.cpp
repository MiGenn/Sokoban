#include "RenderLayer.h"

#include <cassert>

RenderLayer::RenderLayer(HDC referenceContext, Vector2i size) NOEXCEPT_WHEN_NDEBUG :
	m_isUsed(false), m_size(size)
{
	assert(size.x > 0 && size.y > 0);

	m_context = CreateCompatibleDC(referenceContext);
	assert(m_context != NULL);
	auto bitmap = CreateCompatibleBitmap(referenceContext, size.x, size.y);
	m_initialBitmap = SelectObject(m_context, bitmap);
}

RenderLayer::~RenderLayer() noexcept
{
	auto bitmap{ SelectObject(m_context, m_initialBitmap) };
	DeleteObject(bitmap);
	DeleteDC(m_context);
}

HDC RenderLayer::GetMemoryContext() noexcept
{
	m_isUsed = true;

	return m_context;
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

	m_size = newSize;
	auto newBitmap{ CreateCompatibleBitmap(referenceContext, newSize.x, newSize.y) };
	assert(newBitmap != NULL);
	HGDIOBJ oldBitmap{ SelectObject(m_context, newBitmap) };

	DeleteObject(oldBitmap);
}
