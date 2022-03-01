#pragma once
#include "WindowClass.h"

class EditorWindow final : public Window
{
public:
	EditorWindow(int width, int height);

private:
	LRESULT HandleMessages(UINT message, WPARAM wParam, LPARAM lParam) override;

	class Class : public WindowClass
	{
	public:
		static const Class editorClass;

	private:
		Class();
		Class(const Class&) = delete;
		Class& operator=(const Class&) = delete;
	};
};
