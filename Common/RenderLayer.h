#pragma once
#include "MemoryDC.h"
#include "SelectWrapper.h"
#include "UniqueGDIOBJ.h"
#include "Vector2D.h"
#include "BuildInfo.h"

class RenderLayer
{
public:
	RenderLayer(HDC referenceContext, Vector2i size) NOEXCEPT_WHEN_NDEBUG;
	RenderLayer(const RenderLayer&) = delete;

	RenderLayer& operator=(const RenderLayer&) = delete;

	void Resize(HDC referenceContext, Vector2i newSize) NOEXCEPT_WHEN_NDEBUG;
	bool IsUsed() const noexcept;
	void SetUsed(bool isUsed) noexcept;

	HDC GetMemoryContext() noexcept;
	Vector2i GetSize() const noexcept;

private:
	bool m_isUsed;
	Vector2i m_size;

	Utilities::Winapi::SmartPointer::MemoryDC m_context;
	Utilities::Winapi::SmartPointer::UniqueGDIOBJ<HBITMAP> m_bitmap;
	Utilities::Winapi::Wrapper::SelectWrapper m_bitmapSelectWrapper;
};
