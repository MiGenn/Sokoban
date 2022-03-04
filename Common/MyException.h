#pragma once
#include <exception>
#include <string>
#include <sstream>

class MyException : public std::exception
{
public:
	MyException(int line, const char* file);

	virtual const char* what() const override final;
	virtual const char* GetType() const = 0;

protected:
	mutable std::string m_whatBuffer;

	const std::string& GetOrigin() const;

private:
	std::string m_origin;
};
