#ifndef BLINKY_H
#define BLINKY_H

#include "ghost.h"

class Blinky: public Ghost
{
private:
    Board* parent;
    QPoint scatterCornerLeft(){return QPoint(21,5);}
    QPoint scatterCornerRight(){return QPoint(26,1);}
public:
    Blinky(int posx, int posy, Board* parent = 0);
    QPoint ghostDestination() override;
};

#endif // BLINKY_H
