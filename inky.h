#ifndef INKY_H
#define INKY_H

#include "ghost.h"

class Inky: public Ghost
{
private:
    Board* parent;
    QPoint scatterCornerLeft(){return QPoint(1,1);}
    QPoint scatterCornerRight(){return QPoint(6,5);}
public:
    Inky(int posx, int posy, Board* parent = 0);
    QPoint ghostDestination() override;
};

#endif // INKY_H
