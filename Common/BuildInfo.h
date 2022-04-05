#pragma once

namespace BuildInfo
{
	constexpr bool isDebug =
		#ifdef _DEBUG
		true
		#else
		false
		#endif
		;
}

#define NOEXCEPT_WHEN_NDEBUG noexcept(!BuildInfo::isDebug)