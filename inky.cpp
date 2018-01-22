#include "inky.h"
#include <qpoint.h>
Inky::Inky(int posx, int posy, Board* parent)
    :Ghost(posx,posy,Inky::Cyan,parent)
{
    this->parent = parent;
    direction = Up;
}
QPoint Inky::ghostDestination()
{
    int x=0,y=0;
    if(!isGhostDead())
    {
        if(!isScatter())
        {
            int pacmanXID = parent->pacman->PosXID();
            int pacmanYID = parent->pacman->PosYID();
            int blinkyXID = parent->ghostContainer.last()->PosXID();
            int blinkyYID = parent->ghostContainer.last()->PosYID();
            x = pacmanXID - blinkyXID;
            y = pacmanYID - blinkyYID;
            return QPoint(pacmanXID + x,pacmanYID + y);
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
