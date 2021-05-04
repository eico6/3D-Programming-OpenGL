#include "collisionbox.h"

CollisionBox::CollisionBox()
{
    // These values are used to check if collision should be active for a particular object.
    p1 = QVector2D(0.0f, 0.0f);
    p2 = QVector2D(0.0f, 0.0f);
}

CollisionBox::CollisionBox(const QVector2D &lowerLeft, const QVector2D &upperRight)
{
    p1 = lowerLeft;
    p2 = upperRight;
}

bool CollisionBox::collisionBoxIsActive()
{
    // Checks if the collision box is assigned default values
    if ((p1 == QVector2D(0.0f, 0.0f)) &&
         p2 == QVector2D(0.0f, 0.0f)){
         return false;
    }

    return true;
}
