#include "SelectWrapper.h"

SelectWrapper::SelectWrapper(HDC context, HGDIOBJ object) noexcept 
{
	Reset(context, object);
}

SelectWrapper::~SelectWrapper() noexcept
{
	if (m_context != NULL && m_previousObject != NULL)
		SelectObject(m_context, m_previousObject);
}

void SelectWrapper::Reset(HDC context, HGDIOBJ object) noexcept
{
	this->~SelectWrapper();
	m_context = context;
	m_previousObject = SelectObject(context, object);
}
