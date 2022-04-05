#include "MyException.h"

#include <sstream>

MyException::MyException(int line, const char* file) noexcept
{
	std::stringstream ss;
	ss << "FILE: " << file << '\n' <<
		"LINE: " << line;

	m_origin = ss.str();
}

const char* MyException::what() const noexcept
{
	return m_whatBuffer.c_str();
}

const std::string& MyException::GetOrigin() const noexcept
{
	return m_origin;
}
