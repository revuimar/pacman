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
    enum Shape {Rect,Dot,PacDot,PacMan};
private:
    Board* parent;
    QRectF rect;

    Shape shape;
public:
    Particle(int posx,int posy,Shape chosen, Board* parent = 0);
    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

    static bool isMapBoundary(Particle* object);
    static bool isThereDot(Particle* object);
    static bool isTherePellet(Particle* object);
    int PosTop();
    int PosBottom();
    int PosLeft();
    int PosRight();
    int PosYID();
    int PosXID();
};
#endif // PARTICLE_H
