#pragma once
#include <cmath>
#include <limits>

namespace Utilities::Cpp
{
	static constexpr float epsilonF{ std::numeric_limits<float>::epsilon() };

	bool AreEqual(float left, float right, float epsilon = epsilonF) noexcept;
	bool IsGreaterThanOrEqual(float left, float right, float epsilon = epsilonF) noexcept;
	bool IsLessThanOrEqual(float left, float right, float epsilon = epsilonF) noexcept;
	bool IsGreaterThan(float left, float right, float epsilon = epsilonF) noexcept;
	bool IsLessThan(float left, float right, float epsilon = epsilonF) noexcept;
}
