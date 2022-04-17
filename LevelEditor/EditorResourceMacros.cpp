#include "EditorResourceMacros.h"

#include <cassert>

bool SubMenuUtilities::IsOwned(int itemID, int subMenuID)
{
	assert(subMenuID >= 0 && subMenuID <= 2);
	assert((itemID >= 30001 && subMenuID <= 30006) ||
		itemID >= 40001 && subMenuID <= 40005 ||
		itemID >= 50001 && subMenuID <= 50002);

	switch (subMenuID)
	{
	case ID_FILE:
		if (itemID >= 30001 && itemID <= 30006)
			return true;
		break;

	case ID_GAMEOBJECTS:
		if (itemID >= 40001 && itemID <= 40005)
			return true;
		break;

	case ID_SIMULATION:
		if (itemID >= 50001 && itemID <= 50002)
			return true;
		break;
	}

    return false;
}
