#include "Collision2D.h"

#include "WinapiException.h"
#include "NumberComparison.h"

bool Collision2D::IsCollision(Vector2f firstRectPosition, Vector2f firstRectSize, 
    Vector2f secondRectPosition, Vector2f secondRectSize) noexcept
{
    firstRectSize.y *= -1;
    secondRectSize.y *= -1;
    const RectF firstRect(firstRectPosition, firstRectPosition + firstRectSize);
    const RectF secondRect(secondRectPosition, secondRectPosition + secondRectSize);

    return IsCollision(firstRect, secondRect);
}

bool Collision2D::IsCollision(const RectF& firstRect, const RectF& secondRect) noexcept
{
    return firstRect.topLeft.x < secondRect.bottomRight.x && firstRect.bottomRight.x > secondRect.topLeft.x &&
        firstRect.topLeft.y > secondRect.bottomRight.y && firstRect.bottomRight.y < secondRect.topLeft.y;
}
