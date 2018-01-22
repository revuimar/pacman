#include "clyde.h"
#include <qpoint.h>
#include <math.h>
Clyde::Clyde(int posx, int posy, Board* parent)
    :Ghost(posx,posy,Clyde::Orange,parent)
{
    this->parent = parent;
    direction = Up;
}
QPoint Clyde::ghostDestination()
{
    int x=0,y=0;
    if(!isGhostDead())
    {
        if(!isScatter())
        {
            int pacmanXID = parent->pacman->PosXID();
            int pacmanYID = parent->pacman->PosYID();
            int clydeXID = PosXID();
            int clydeYID = PosYID();
            x = pacmanXID - clydeXID;
            y = pacmanYID - clydeYID;
            if(floor(sqrt(x*x+y*y))< 4) return QPoint(1,29);
            else return QPoint(pacmanXID,pacmanYID);
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
    return QPoint(0,0);
}
