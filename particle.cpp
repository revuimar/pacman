#include "particle.h"
#include "ui_mainwindow.h"
#include "board.h"
#include <QPen>
#include <QSize>
#include <QBrush>
#include <QRect>
#include <QPainter>
#include <QDebug>
Particle::Particle(int posx, int posy, Shape chosen,Board* parent)
    :QGraphicsRectItem(posx,posy,20,20)
{
    this->parent = parent;
    rect = QRect(posx,posy,20,20);
    shape = chosen;
}
void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (shape) {
    case Rect:
        painter->setBrush(QBrush(QColor("blue")));
        painter->drawRect(rect);
        break;
    case Dot:
        painter->setBrush(QBrush(QColor("red")));
        rect.setRect(rect.center().x()-2.5,rect.center().y()-2.5,5,5);
        painter->drawEllipse(rect);
        break;
    case PacMan:
        painter->setBrush(QBrush(QColor("yellow")));
        painter->drawEllipse(rect);
        break;
    case PacDot:
        painter->setBrush(QBrush(QColor("orange")));
        rect.setRect(rect.center().x()-5,rect.center().y()-5,10,10);
        painter->drawEllipse(rect);
        break;
    default:
        break;
    }
    update();
}
bool Particle::isMapBoundary(Particle* object)
{
    if(object == nullptr) return false;
    if(object->shape == Rect){
        return true;
    }
    return false;
}
bool Particle::isThereDot(Particle* object)
{
    if(object == nullptr) return false;
    if(object->shape == Dot){
        return true;
    }
    return false;
}
bool Particle::isTherePellet(Particle* object)
{
    if(object == nullptr) return false;
    if(object->shape == PacDot){
        return true;
    }
    return false;
}
int Particle::PosLeft()
{
    return ((rect.left()+x()));
}
int Particle::PosTop()
{
    return ((rect.top()+y()));
}
int Particle::PosBottom()
{
    return ((rect.bottom()+y()));
}
int Particle::PosRight()
{
    return ((rect.right()+x()));
}
int Particle::PosXID()
{
    return floor((rect.center().x()+x()));
}
int Particle::PosYID()
{
    return floor((rect.center().y()+y()));
}
