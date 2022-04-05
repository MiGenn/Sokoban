#pragma once
#include <exception>
#include <string>

class MyException : public std::exception
{
public:
	MyException(int line, const char* file) noexcept;

	virtual const char* what() const noexcept override final;
	virtual const char* GetType() const noexcept = 0;

protected:
	mutable std::string m_whatBuffer;

	const std::string& GetOrigin() const noexcept;

private:
	std::string m_origin;
};
