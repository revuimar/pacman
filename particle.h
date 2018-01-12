#ifndef PARTICLE_H
#define PARTICLE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include "board.h"
class Board;
class Particle:public QGraphicsRectItem
{
public:
    enum Shape {Rect,Dot,PacDot};
private:
    Board* parent;
    QRectF rect;

    Shape shape;
public:
    Particle(int posx,int posy,Shape chosen, Board* parent = 0);
    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);


};

#endif // PARTICLE_H
