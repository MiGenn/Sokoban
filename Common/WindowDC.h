#pragma once
#include "BuildInfo.h"
#include "Window.h"

namespace Utilities::Winapi::SmartPointer
{
	class WindowDC final
	{
	public:
		WindowDC(const Window* window) NOEXCEPT_WHEN_NDEBUG;
		WindowDC(const WindowDC&) = delete;
		~WindowDC() noexcept;

		WindowDC& operator=(const WindowDC&) = delete;

		HDC Get() const noexcept;

	private:
		const Window* const m_window;
		HDC m_windowContext;
	};
}
