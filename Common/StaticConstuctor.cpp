#include "StaticConstuctor.h"

Utilities::Cpp::StaticConstructor::StaticConstructor(void(*constructingFunction)()) noexcept
{
	constructingFunction();
}
