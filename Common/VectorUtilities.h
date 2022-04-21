#pragma once
#include <vector>
#include <memory>
#include "UniquePointerUtilities.h"

namespace VectorUtilities
{
	template<std::copyable T>
	std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::unique_ptr<T>>& vector)
	{
		std::vector<std::unique_ptr<T>> outputVector;
		outputVector.reserve(vector.size());
		for (auto& element : vector)
			outputVector.push_back(UniquePointerUtilities::Duplicate(element)); 

		return outputVector;
	}
};
