#include "Game.h"
#include "SerializableObjectFactory.h"

int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
	static constexpr UINT messageBoxType{ MB_OK | MB_ICONEXCLAMATION };
	
	try
	{
		return Game().Run();
	}
	catch (const MyException& e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), messageBoxType);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard exeption", messageBoxType);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No details are available", "Unknown exeption", messageBoxType);
	}

	return -1;
}