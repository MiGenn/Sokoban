#pragma once
#include <string>

namespace Utilities::Cpp::Path
{
	class Path final
	{
	public:
		Path() noexcept = default;
		Path(const std::wstring& fullPath);
		Path(std::wstring&& fullPath);

		void SetFullPath(const std::wstring& fullPath) noexcept;
		void SetFullPath(std::wstring&& fullPath) noexcept;
		void SetPath(const std::wstring& path) noexcept;
		void SetPath(std::wstring&& path) noexcept;
		void SetFullName(const std::wstring& fullName) noexcept;
		void SetFullName(std::wstring&& fullName) noexcept;

		const std::wstring& GetFullPath() const noexcept;
		const std::wstring& GetPath() const noexcept;
		const std::wstring& GetFullName() const noexcept;

		void ClearFullPath() noexcept;
		void ClearPath() noexcept;
		void ClearFullName() noexcept;

		bool IsFullPathValid() const noexcept;
		bool IsFullPathEmpty() const noexcept;
		bool IsPathEmpty() const noexcept;
		bool IsFullNameEmpty() const noexcept;

	private:
		std::wstring m_fullPath;

		std::wstring m_path;
		std::wstring m_fullName;

		void UpdateFullPath() noexcept;
		void UpdatePathParts() noexcept;
	};
}
