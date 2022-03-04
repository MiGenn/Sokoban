#pragma once
#include "Application.h"
#include "EditorWindow.h"

class Editor final : public Application
{
public:
	Editor();
	Editor(const Editor&) = delete;

	Editor& operator=(const Editor&) = delete;

	int Run() override;

private:
	EditorWindow m_window;
};
