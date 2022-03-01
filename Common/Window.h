#pragma once
#include "WinapiException.h"
#include "Vector2D.h"

class Window
{
public:
	friend class WindowClass;

	Window(int width, int height);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void Resize(int width, int height);
	class DeviceContextWrapper GetDeviceContext();
	HWND GetHandle() const;
	Vector2i GetSize() const;

protected:
	int m_width, m_height;
	HWND m_handle;

	virtual LRESULT HandleMessages(UINT message, WPARAM wParam, LPARAM lParam) = 0;
};
