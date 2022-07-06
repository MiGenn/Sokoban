#pragma once
#include "WinapiException.h"

namespace Utilities::Winapi::Wrapper
{
	class SelectWrapper final
	{
	public:
		SelectWrapper() noexcept = default;
		SelectWrapper(HDC context, HGDIOBJ object) noexcept;
		SelectWrapper(const SelectWrapper&) = delete;
		~SelectWrapper() noexcept;

		SelectWrapper& operator=(const SelectWrapper&) = delete;

		void Reset(HDC context = nullptr, HGDIOBJ object = nullptr) noexcept;

	private:
		HDC m_context{ nullptr };
		HGDIOBJ m_previousObject{ nullptr };
	};
}
