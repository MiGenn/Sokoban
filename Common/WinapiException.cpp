#include "WinapiException.h"

WinapiException::WinapiException(int line, const char* file, HRESULT errorCode) :
	MyException(line, file)
{
	std::stringstream ss;
	ss << "ERROR CODE: " << std::hex << errorCode << '\n' <<
		"DESCRIPTION: " << TranslateErrorCode(errorCode) << '\n' <<
		GetOrigin();

	m_whatBuffer = ss.str();
}

const char* WinapiException::GetType() const
{
	return "Window Exception";
}

std::string WinapiException::TranslateErrorCode(HRESULT errorCode)
{
	char* messageBuffer;
	DWORD messageBufferSize = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&messageBuffer), 0, nullptr);

	if (messageBufferSize == 0)
		return "Undefined error code";

	std::string errorDescription{ messageBuffer };
	LocalFree(messageBuffer);

	return errorDescription;
}