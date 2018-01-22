#include "blinky.h"
#include <qpoint.h>
Blinky::Blinky(int posx, int posy, Board* parent)
    :Ghost(posx,posy,Blinky::Red,parent)
{
    this->parent = parent;
    direction = Left;
    outOfTheHouse = false;
}
QPoint Blinky::ghostDestination()
{
    int x=0,y=0;
    if(!isGhostDead())
    {
        if(!isScatter())
        {
            switch(parent->pacman->direction)
            {
                case Pacman::LEFT:
                    x=1;
                    break;
                case Pacman::RIGHT:
                    x=-1;
                    break;
                case Pacman::UP:
                    y=1;
                    break;
                case Pacman::DOWN:
                    y=-1;
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
