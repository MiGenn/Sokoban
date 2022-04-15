#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <commdlg.h>
#include <shlobj_core.h>
#include "MyException.h"

#pragma comment(lib, "comdlg32")

class WinapiException final : public MyException
{
public:
	WinapiException(int line, const char* file, HRESULT errorCode) noexcept;

	const char* GetType() const noexcept override;

private:
	static std::string TranslateErrorCode(HRESULT errorCode) noexcept;
};

#define WINAPI_EXCEPTION(errorCode) WinapiException(__LINE__, __FILE__, errorCode)
#define WINAPI_LAST_EXCEPTION() WinapiException(__LINE__, __FILE__, GetLastError())
