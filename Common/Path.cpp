#include "Path.h"

#include "PathUtilities.h"

Path::Path(const std::wstring& fullPath)
{
	SetFullPath(fullPath);
}

Path::Path(std::wstring&& fullPath)
{
	SetFullPath(std::move(fullPath));
}

void Path::SetFullPath(const std::wstring& fullPath) noexcept
{
	m_fullPath = fullPath;

	UpdatePathParts();
}

void Path::SetFullPath(std::wstring&& fullPath) noexcept
{
	m_fullPath = std::move(fullPath);

	UpdatePathParts();
}

void Path::SetPath(const std::wstring& path) noexcept
{
	m_path = path;

	UpdateFullPath();
}

void Path::SetPath(std::wstring&& path) noexcept
{
	m_path = std::move(path);

	UpdateFullPath();
}

void Path::SetFullName(const std::wstring& fullName) noexcept
{
	m_fullName = fullName;

	UpdateFullPath();
}

void Path::SetFullName(std::wstring&& fullName) noexcept
{
	m_fullName = std::move(fullName);

	UpdateFullPath();
}

const std::wstring& Path::GetFullPath() const noexcept
{
	return m_fullPath;
}

const std::wstring& Path::GetPath() const noexcept
{
	return m_path;
}

const std::wstring& Path::GetFullName() const noexcept
{
	return m_fullName;
}

void Path::ClearFullPath() noexcept
{
	m_fullPath.clear();

	UpdatePathParts();
}

void Path::ClearPath() noexcept
{
	m_path.clear();

	UpdateFullPath();
}

void Path::ClearFullName() noexcept
{
	m_fullName.clear();

	UpdateFullPath();
}

bool Path::IsFullPathValid() const noexcept
{
	if (IsFullPathEmpty())
		return true;

	if (IsPathEmpty() || IsFullNameEmpty())
		return false;

	return true;
}

bool Path::IsFullPathEmpty() const noexcept
{
	return m_fullPath.empty();
}

bool Path::IsPathEmpty() const noexcept
{
	return m_path.empty();
}

bool Path::IsFullNameEmpty() const noexcept
{
	return m_fullName.empty();
}

void Path::UpdateFullPath() noexcept
{
	m_fullPath = m_path + m_fullName;
}

void Path::UpdatePathParts() noexcept
{
	m_path = PathUtilities::ExtractPath(m_fullPath);
	m_fullName = PathUtilities::ExtractFullName(m_fullPath);
}
