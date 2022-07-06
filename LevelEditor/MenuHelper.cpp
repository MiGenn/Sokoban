#include "MenuHelper.h"

#include <cassert>
#include "EditorResourceMacros.h"

bool MenuHelper::IsOwned(int itemID, int subMenuID) NOEXCEPT_WHEN_NDEBUG
{
	assert(subMenuID >= ID_FILE && subMenuID <= ID_SIMULATION);
	assert((itemID >= ID_FILE_CREATE && subMenuID <= ID_FILE_RENAME) ||
		itemID >= ID_GAMEOBJECTS_WALL && subMenuID <= ID_GAMEOBJECTS_CHARACTER ||
		itemID >= ID_SIMULATION_STOP && subMenuID <= ID_SIMULATION_PLAY);

	switch (subMenuID)
	{
	case ID_FILE:
		if (itemID >= ID_FILE_CREATE && itemID <= ID_FILE_RENAME)
			return true;
		break;

	case ID_GAMEOBJECTS:
		if (itemID >= ID_GAMEOBJECTS_WALL && itemID <= ID_GAMEOBJECTS_CHARACTER)
			return true;
		break;

	case ID_SIMULATION:
		if (itemID >= ID_SIMULATION_STOP && itemID <= ID_SIMULATION_PLAY)
			return true;
		break;
	}

	return false;
}
