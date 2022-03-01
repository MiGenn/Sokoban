#include "MyException.h"

MyException::MyException(int line, const char* file)
{
	std::stringstream ss;
	ss << "FILE: " << file << '\n' <<
		"LINE: " << line;

	m_origin = ss.str();
}

const char* MyException::what() const
{
	return m_whatBuffer.c_str();
}

const std::string& MyException::GetOrigin() const
{
	return m_origin;
}
