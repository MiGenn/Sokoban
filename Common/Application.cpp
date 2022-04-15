#include "Application.h"

#include "WinapiException.h"

std::optional<int> Application::RetrieveAndRouteMessages()
{
	static MSG messageStruct{};
	while (PeekMessage(&messageStruct, NULL, NULL, NULL, PM_REMOVE))
	{
		if (messageStruct.message == WM_QUIT)
			return static_cast<int>(messageStruct.wParam);

		TranslateMessage(&messageStruct);
		DispatchMessage(&messageStruct);
	}

	return {};
}
