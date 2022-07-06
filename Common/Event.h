#pragma once
#include <functional>
#include <unordered_map>
#include <stdexcept>

namespace Utilities::Cpp
{
	template<class... FunctionParams>
	class Event final
	{
	public:
		using Function = std::function<void(FunctionParams...)>;

		Event() noexcept {};
		Event(const Event&) = delete;

		Event& operator=(const Event&) = delete;

		unsigned long long operator+=(Function subscribingFunction)
		{
			if (!subscribingFunction)
				throw std::logic_error("Subscribing function is nullptr");

			auto functionID{ nextAvailableID++ };
			m_subscribingFunctions.emplace(functionID, subscribingFunction);

			return functionID;
		}

		void operator-=(unsigned long long unsubscribingFunctionID) noexcept
		{
			auto unsubscribingFunctionIterator{ m_subscribingFunctions.find(unsubscribingFunctionID) };
			if (unsubscribingFunctionIterator != m_subscribingFunctions.end())
				m_subscribingFunctions.erase(unsubscribingFunctionIterator);
		}

		void Trigger(FunctionParams... args) const noexcept
		{
			for (auto& IDAndFunction : m_subscribingFunctions)
				IDAndFunction.second(args...);
		}

	private:
		unsigned long long nextAvailableID{ 0ull };
		std::unordered_map<unsigned long long, Function> m_subscribingFunctions;
	};
}
