#include "Entity2D.h"

Entity2D::Entity2D()
{
	components.emplace_back(new Transform2D{});
	components.emplace_back(nullptr);
}
