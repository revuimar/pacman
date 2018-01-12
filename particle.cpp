#include "particle.h"
#include "board.h"
#include <QPen>
#include <QSize>
#include <QBrush>
#include <QRect>
#include <QPainter>
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
    case PacDot:
        painter->setBrush(QBrush(QColor("orange")));
        rect.setRect(rect.center().x()-5,rect.center().y()-5,10,10);
        painter->drawEllipse(rect);
        break;
    default:
        break;
    }
}
