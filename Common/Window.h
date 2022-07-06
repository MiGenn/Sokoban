#pragma once
#include "WinapiException.h"
#include "Vector2D.h"
#include "BuildInfo.h"

namespace Utilities::Winapi::SmartPointer
{
	class WindowDC;
}

class Window
{
public:
	friend class WindowClass;

	Window(Vector2i size) NOEXCEPT_WHEN_NDEBUG;
	Window(const Window&) = delete;

	Window& operator=(const Window&) = delete;

	virtual void Resize(Vector2i size);
	Utilities::Winapi::SmartPointer::WindowDC GetDeviceContext() noexcept;
	HWND GetHandle() const noexcept;
	Vector2i GetSize() const noexcept;

protected:
	Vector2i m_size;
	HWND m_handle{ nullptr };

	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
};
