#pragma once
#include <optional>

class Application
{
public:
	virtual int Run() = 0;

protected:
	Application() = default;
	Application(const Application&) = delete;

	Application& operator=(const Application&) = delete;

	virtual std::optional<int> RetrieveAndRouteMessages();
};
