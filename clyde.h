#ifndef CLYDE_H
#define CLYDE_H

#include "ghost.h"

class Clyde: public Ghost
{
private:
    Board* parent;
    QPoint scatterCornerLeft(){return QPoint(15,26);}
    QPoint scatterCornerRight(){return QPoint(26,29);}
public:
    Clyde(int posx, int posy, Board* parent = 0);
    QPoint ghostDestination() override;
};

#endif // CLYDE_H
