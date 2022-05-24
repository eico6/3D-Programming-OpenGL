#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

#include <QVector2D>

enum Coords{
    X = 0,
    Z = 1
};

struct CollisionBox
{    
    CollisionBox();
    CollisionBox(const QVector2D &lowerLeft, const QVector2D &upperRight);
    bool collisionBoxIsActive();
    QVector2D p1; // Lower-left  corner
    QVector2D p2; // Upper-right corner
};

#endif // COLLISIONBOX_H
