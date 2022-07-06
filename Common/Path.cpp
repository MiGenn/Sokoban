#include "Path.h"

#include "PathUtilities.h"

Utilities::Cpp::Path::Path::Path(const std::wstring& fullPath)
{
	SetFullPath(fullPath);
}

Utilities::Cpp::Path::Path::Path(std::wstring&& fullPath)
{
	SetFullPath(std::move(fullPath));
}

void Utilities::Cpp::Path::Path::SetFullPath(const std::wstring& fullPath)
{
	m_fullPath = fullPath;
	UpdatePathParts();
}

void Utilities::Cpp::Path::Path::SetFullPath(std::wstring&& fullPath)
{
	m_fullPath = std::move(fullPath);
	UpdatePathParts();
}

void Utilities::Cpp::Path::Path::SetPath(const std::wstring& path) noexcept
{
	m_path = path;
	UpdateFullPath();
}

void Utilities::Cpp::Path::Path::SetPath(std::wstring&& path) noexcept
{
	m_path = std::move(path);
	UpdateFullPath();
}

void Utilities::Cpp::Path::Path::SetFullName(const std::wstring& fullName) noexcept
{
	m_fullName = fullName;
	UpdateFullPath();
}

void Utilities::Cpp::Path::Path::SetFullName(std::wstring&& fullName) noexcept
{
	m_fullName = std::move(fullName);
	UpdateFullPath();
}

const std::wstring& Utilities::Cpp::Path::Path::GetFullPath() const noexcept
{
	return m_fullPath;
}

const std::wstring& Utilities::Cpp::Path::Path::GetPath() const noexcept
{
	return m_path;
}

const std::wstring& Utilities::Cpp::Path::Path::GetFullName() const noexcept
{
	return m_fullName;
}

void Utilities::Cpp::Path::Path::ClearFullPath() noexcept
{
	m_fullPath.clear();
	UpdatePathParts();
}

void Utilities::Cpp::Path::Path::ClearPath() noexcept
{
	m_path.clear();
	UpdateFullPath();
}

void Utilities::Cpp::Path::Path::ClearFullName() noexcept
{
	m_fullName.clear();
	UpdateFullPath();
}

bool Utilities::Cpp::Path::Path::IsFullPathValid() const noexcept
{
	if (IsFullPathEmpty())
		return true;

	if (IsPathEmpty() || IsFullNameEmpty())
		return false;

	return true;
}

bool Utilities::Cpp::Path::Path::IsFullPathEmpty() const noexcept
{
	return m_fullPath.empty();
}

bool Utilities::Cpp::Path::Path::IsPathEmpty() const noexcept
{
	return m_path.empty();
}

bool Utilities::Cpp::Path::Path::IsFullNameEmpty() const noexcept
{
	return m_fullName.empty();
}

void Utilities::Cpp::Path::Path::UpdateFullPath() noexcept
{
	m_fullPath = m_path + m_fullName;
}

void Utilities::Cpp::Path::Path::UpdatePathParts()
{
	m_path = Utilities::Cpp::Path::ExtractPath(m_fullPath);
	m_fullName = Utilities::Cpp::Path::ExtractFullName(m_fullPath);
}
