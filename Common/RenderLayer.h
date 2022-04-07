#pragma once
#include "Vector2D.h"
#include "BuildInfo.h"

class RenderLayer
{
public:
	RenderLayer(HDC referenceContext, Vector2i size) NOEXCEPT_WHEN_NDEBUG;
	RenderLayer(const RenderLayer&) = delete;
	~RenderLayer() noexcept;

	RenderLayer& operator=(const RenderLayer&) = delete;

	void Resize(HDC referenceContext, Vector2i newSize) NOEXCEPT_WHEN_NDEBUG;
	bool IsUsed() const noexcept;
	void SetUsed(bool isUsed) noexcept;

	HDC GetMemoryContext() noexcept;
	Vector2i GetSize() const noexcept;

private:
	Vector2i m_size;
	HDC m_context;
	bool m_isUsed;

	HGDIOBJ m_initialBitmap;
};

