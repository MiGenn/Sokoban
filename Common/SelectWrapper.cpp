#include "SelectWrapper.h"

Utilities::Winapi::Wrapper::SelectWrapper::SelectWrapper(HDC context, HGDIOBJ object) noexcept
{
	Reset(context, object);
}

Utilities::Winapi::Wrapper::SelectWrapper::~SelectWrapper() noexcept
{
	if (m_context && m_previousObject)
		SelectObject(m_context, m_previousObject);
}

void Utilities::Winapi::Wrapper::SelectWrapper::Reset(HDC context, HGDIOBJ object) noexcept
{
	this->~SelectWrapper();
	m_context = context;
	m_previousObject = SelectObject(context, object);
}
