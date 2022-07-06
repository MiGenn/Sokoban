#include "NumberComparison.h"

#include <cmath>

bool Utilities::Cpp::AreEqual(float left, float right, float epsilon) noexcept
{
	return fabs(left - right) <= std::min(fabs(left), fabs(right)) * epsilon;
}

bool Utilities::Cpp::IsGreaterThanOrEqual(float left, float right, float epsilon) noexcept
{
	return IsGreaterThan(left, right) || AreEqual(left, right);
}

bool Utilities::Cpp::IsLessThanOrEqual(float left, float right, float epsilon) noexcept
{
	return IsLessThan(left, right) || AreEqual(left, right);
}

bool Utilities::Cpp::IsGreaterThan(float left, float right, float epsilon) noexcept
{
	return left - right > std::max(fabs(left), fabs(right)) * epsilon;
}

bool Utilities::Cpp::IsLessThan(float left, float right, float epsilon) noexcept
{
	return right - left > std::max(fabs(left), fabs(right)) * epsilon;
}

