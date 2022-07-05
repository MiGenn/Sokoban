#pragma once
#include "WindowClass.h"
#include "Graphics2D.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Level.h"
#include "ChangeWrapper.h"
#include "Path.h"
#include "Event.h"

class EditorWindow final : public Window
{
public:
	Utilities::Cpp::Event<> simulationStarted;
	Utilities::Cpp::Event<> simulationEnded;

	Keyboard keyboard;
	Mouse mouse;
	Graphics2D graphics;

	EditorWindow(Vector2i size);

	bool TryLoadLevel(const std::wstring& fullPath);
	const Level* GetLevel() const noexcept;
	bool IsSimulation() const noexcept;

private:
	enum class HotKey
	{
		ControlS
	};

	enum class ChangeSubmenuOption
	{
		Disable = MF_DISABLED,
		Enable = MF_ENABLED
	};

	static const std::wstring m_editorName;
	static constexpr const wchar_t* m_levelFilter{ L"Level Files\0*.lvl\0" };
	static const std::wstring m_levelHintText;

	Utilities::ChangeWrapper<Level> m_level{ nullptr };
	Utilities::Cpp::Path::Path m_levelPath;
	std::unique_ptr<TiledEntity> m_currentEntity;
	bool m_isSimulation{ false };
	Vector2f m_cameraPositionBeforeSimulation;
	float m_scrollSensitivity{ 0.1f };
	float m_drawingOriginMoveSensitivity{ 1.f };

	LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) override;
	void RegisterHotKeys();

	void OnClose();
	void OnCommand(int controlID);
	void OnHotkey(HotKey hotKey);
	void OnLeftButtonClick(POINTS position);
	void OnRightButtonClick(POINTS position);
	void OnMouseScroll();

	void OnCreateButtonClick();
	void OnLoadButtonClick();
	void OnUnloadButtonClick();
	void OnSaveButtonClick();
	void OnSaveAsButtonClick();
	void OnRenameButtonClick();

	void OnWallButtonClick();
	void OnRoadButtonClick();
	void OnPointButtonClick();
	void OnBoxButtonClick();
	void OnCharacterButtonClick();

	void OnPlayButtonClick();
	void OnStopButtonClick();

	void OnLevelDeletedOrLoaded();
	void OnLevelPathChanged();
	void ChangeSubmenusWhenLevelIsDeletedOrLoaded(ChangeSubmenuOption option);
	void ChangeSubmenusWhenSimulation(ChangeSubmenuOption option);

	void SetCurrentEntityPosition(POINTS screenCoords);
	void MoveLevel();

	std::wstring GetPathFromUser();
	std::wstring GetLevelFullNameFromUser();

	bool TrySaveLevelIntoFile();
	bool TryLoadLevelFromFile(const std::wstring& fullPath);
	bool TryValidateLevelPathIfInvalid();
	bool TryValidateFullPathIfAnotherFileExists(const std::wstring& validNewPath, const std::wstring& newFullName);
	bool CanContinueBeforeDeletingOrResetingLevel();
	bool CanDeleteOrAddEntity();
	bool IsLevelValid();

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
