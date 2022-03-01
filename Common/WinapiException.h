#pragma once
#define WIN32_LEAN_AND_MEAN

#include "MyException.h"
#include "windows.h"

class WinapiException : public MyException
{
public:
	WinapiException(int line, const char* file, HRESULT errorCode);

	const char* GetType() const override;

private:
	static std::string TranslateErrorCode(HRESULT errorCode);
};

#define EXCEPTION(errorCode) WinapiException(__LINE__, __FILE__, errorCode)
#define LAST_EXCEPTION() WinapiException(__LINE__, __FILE__, GetLastError())
