#pragma once
#include <memory>
#include <stdexcept>

namespace Utilities
{
	template <class T>
	class ChangeWrapper
	{
	public:
		ChangeWrapper(T* instance) noexcept;
		ChangeWrapper(const ChangeWrapper<T>&) = delete;

		ChangeWrapper<T>& operator=(const ChangeWrapper<T>&) = delete;

		const T& Get() const noexcept;
		T& GetForEditing() noexcept;

		void ResetObject(T* newInstance) noexcept;
		void ResetState() noexcept;
		bool IsChanged() const noexcept;
		bool IsNull() const noexcept;

	private:
		std::unique_ptr<T> m_instance;
		bool m_isChanged{ false };
	};

	template<class T>
	inline ChangeWrapper<T>::ChangeWrapper(T* instance) noexcept :
		m_instance(instance)
	{

	}

	template<class T>
	inline const T& ChangeWrapper<T>::Get() const noexcept
	{
		return *m_instance;
	}

	template<class T>
	inline T& ChangeWrapper<T>::GetForEditing() noexcept
	{
		m_isChanged = true;
		return *m_instance;
	}

	template<class T>
	inline void ChangeWrapper<T>::ResetObject(T* newInstance) noexcept
	{
		m_instance.reset(newInstance);
		m_isChanged = true;
	}

	template<class T>
	inline void ChangeWrapper<T>::ResetState() noexcept
	{
		m_isChanged = false;
	}

	template<class T>
	inline bool ChangeWrapper<T>::IsChanged() const noexcept
	{
		return m_isChanged;
	}

	template<class T>
	inline bool ChangeWrapper<T>::IsNull() const noexcept
	{
		return !m_instance.get();
	}
}
