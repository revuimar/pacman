#ifndef PINKY_H
#define PINKY_H

#include "ghost.h"

class Pinky: public Ghost
{
private:
    Board* parent;
    QPoint scatterCornerLeft(){return QPoint(29,1);}
    QPoint scatterCornerRight(){return QPoint(12,6);}
public:
    Pinky(int posx, int posy, Board* parent = 0);
    QPoint ghostDestination() override;
};

#endif // PINKY_H
