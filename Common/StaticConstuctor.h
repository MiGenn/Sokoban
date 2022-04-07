#pragma once

class StaticConstructor
{
public:
	StaticConstructor(void(*constructingFunction)());
	StaticConstructor(const StaticConstructor&) = delete;

	StaticConstructor& operator=(const StaticConstructor&) = delete;
};
