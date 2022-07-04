#pragma once
#include <memory>

namespace Utilities::Cpp::SmartPointer
{
	template <class T1, class T2>
	concept Hierarchy = std::is_base_of_v<T1, T2> || std::is_base_of_v<T2, T1>;

	template<class OutputType, Hierarchy<OutputType> InputType>
	std::unique_ptr<OutputType> StaticCast(std::unique_ptr<InputType>&& input)
	{
		std::unique_ptr<OutputType> output(static_cast<OutputType*>(input.release()));
		return std::move(output);
	}

	template<std::copyable T>
	std::unique_ptr<T> Duplicate(const std::unique_ptr<T>& object)
	{
		return std::make_unique<T>(*object);
	}
}
