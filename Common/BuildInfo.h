#pragma once

namespace Utilities::BuildInfo
{
	constexpr bool isDebug =
		#ifdef _DEBUG
		true
		#else
		false
		#endif
		;
}

#define NOEXCEPT_WHEN_NDEBUG noexcept(!Utilities::BuildInfo::isDebug)