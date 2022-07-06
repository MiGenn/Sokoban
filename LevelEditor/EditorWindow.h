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

	bool TryLoadLevel(const std::wstring& fullPath) noexcept;
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
	void RegisterHotKeys() noexcept;

	void OnClose() noexcept;
	void OnCommand(int controlID) NOEXCEPT_WHEN_NDEBUG;
	void OnHotkey(HotKey hotKey) noexcept;
	void OnLeftButtonClick(POINTS position) noexcept;
	void OnRightButtonClick(POINTS position) noexcept;
	void OnMouseScroll() noexcept;

	void OnCreateButtonClick() noexcept;
	void OnLoadButtonClick() noexcept;
	void OnUnloadButtonClick() noexcept;
	void OnSaveButtonClick() noexcept;
	void OnSaveAsButtonClick() noexcept;
	void OnRenameButtonClick() noexcept;

	void OnWallButtonClick() NOEXCEPT_WHEN_NDEBUG;
	void OnRoadButtonClick() NOEXCEPT_WHEN_NDEBUG;
	void OnPointButtonClick() NOEXCEPT_WHEN_NDEBUG;
	void OnBoxButtonClick() NOEXCEPT_WHEN_NDEBUG;
	void OnCharacterButtonClick() NOEXCEPT_WHEN_NDEBUG;

	void OnPlayButtonClick() noexcept;
	void OnStopButtonClick() noexcept;

	void OnLevelDeletedOrLoaded() noexcept;
	void OnLevelPathChanged() noexcept;
	void ChangeSubmenusWhenLevelIsDeletedOrLoaded(ChangeSubmenuOption option) noexcept;
	void ChangeSubmenusWhenSimulation(ChangeSubmenuOption option) noexcept;

	void SetCurrentEntityPosition(POINTS screenCoords) noexcept;
	void MoveLevel() noexcept;

	std::wstring GetPathFromUser() noexcept;
	std::wstring GetLevelFullNameFromUser() noexcept;

	bool TrySaveLevelIntoFile() noexcept;
	bool TryLoadLevelFromFile(const std::wstring& fullPath) noexcept;
	bool TryValidateLevelPathIfInvalid() noexcept;
	bool TryValidateFullPathIfAnotherFileExists(const std::wstring& validNewPath, const std::wstring& newFullName) noexcept;
	bool CanContinueBeforeDeletingOrResetingLevel() noexcept;
	bool CanDeleteOrAddEntity() const noexcept;
	bool IsLevelValid() noexcept;

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
