#include "Editor.h"

int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR fullPath, _In_ int)
{
	static constexpr UINT messageBoxType{ MB_OK | MB_ICONEXCLAMATION };

	try
	{
		return Editor(L"D:\\test.lvl").Run();
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