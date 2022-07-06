#pragma once

namespace Utilities::Cpp
{
	class StaticConstructor final
	{
	public:
		StaticConstructor(void(*constructingFunction)()) noexcept;
		StaticConstructor(const StaticConstructor&) = delete;

		StaticConstructor& operator=(const StaticConstructor&) = delete;
	};
}
