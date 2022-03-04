#include "Editor.h"

Editor::Editor() :
	m_window(1280, 720)
{

}

int Editor::Run()
{


	while (true)
	{
		if (auto exitCode = RetrieveAndRouteMessages())
			return *exitCode;

		WaitMessage();
	}
}
