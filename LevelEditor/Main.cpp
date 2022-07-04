#include "Editor.h"
#include "StringUtilities.h"

// Змінна fullPathWithQuotationMarks може містити шлях до файлу, який користувач передав відкриваючи файл через LevelEditor
int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR fullPathWithQuotationMarks, _In_ int)
{
	static constexpr UINT messageBoxType{ MB_OK | MB_ICONEXCLAMATION };

	try
	{
		auto fullPath = Utilities::Cpp::String::DeleteFirstAndLastSymbols(fullPathWithQuotationMarks);
		return Editor(fullPath).Run();
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