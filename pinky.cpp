#include "pinky.h"
#include <qpoint.h>
Pinky::Pinky(int posx, int posy, Board* parent)
    :Ghost(posx,posy,Pinky::Pink,parent)
{
    this->parent = parent;
    direction = Up;
}
QPoint Pinky::ghostDestination()
{
    int x=0,y=0;
    if(!isGhostDead())
    {
        if(!isScatter())
        {
            switch(parent->pacman->direction)
            {
                case Pacman::LEFT:
                    x=-4;
                    break;
                case Pacman::RIGHT:
                    x=4;
                    break;
                case Pacman::UP:
                    y=-4;
                    break;
                case Pacman::DOWN:
                    y=4;
                    break;
                default:
                    break;
            }
            return QPoint(parent->pacman->PosXID() + x,parent->pacman->PosYID() + y);
        }
        else
        {
            if(PosXID() <= scatterCornerLeft().x() && PosYID() <= scatterCornerLeft().y())
                return scatterCornerRight();
            else
                return scatterCornerLeft();
        }
    }
    else
    {
        return home();
    }
}
