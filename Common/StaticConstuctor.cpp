#include "StaticConstuctor.h"

StaticConstructor::StaticConstructor(void(*constructingFunction)())
{
	constructingFunction();
}
