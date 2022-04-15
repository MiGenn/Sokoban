#pragma once
#include <string>

template <class T>
concept MoveConstructible = std::is_move_constructible_v<T>;

namespace UnsafeUtilities
{
	template <MoveConstructible T>
	T MakeNonConstForMove(const T& object)
	{
		return std::move(const_cast<T&>(object));
	}
};
