#include "NumberComparison.h"

bool Utilities::Cpp::AreEqual(float a, float b, float epsilon)
{
	return fabs(a - b) <= std::min(fabs(a), fabs(b)) * epsilon;
}
