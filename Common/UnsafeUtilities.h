#pragma once
#include <string>

namespace Utilities::Cpp::Unsafe
{
	template <class T>
	concept MoveConstructible = std::is_move_constructible_v<T>;

	template <MoveConstructible T>
	T&& MakeNonConstForMove(const T& object) noexcept
	{
		return std::move(const_cast<T&>(object));
	}
};
