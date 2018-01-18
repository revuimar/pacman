#include "pacman.h"
#include "ui_mainwindow.h"
#include "board.h"
#include <QPen>
#include <QSize>
#include <QBrush>
#include <QRect>
#include <QPainter>

Pacman::Pacman(int posx, int posy, Board* parent)
    :QGraphicsRectItem(posx,posy,PACMAN_WIDTH,PACMAN_HEIGHT)
{
    this->parent = parent;
    rect = QRect(posx,posy,PACMAN_WIDTH,PACMAN_HEIGHT);
}
void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor("yellow")));
    painter->drawEllipse(rect);
}
int Pacman::PosLeft()
{
    return (static_cast<int>(rect.left()+x()));
}
int Pacman::PosTop()
{
    return (static_cast<int>(rect.top()+y()));
}
int Pacman::PosBottom()
{
    return (static_cast<int>(rect.bottom()+y()));
}
int Pacman::PosRight()
{
    return (static_cast<int>(rect.right()+x()));
}
int Pacman::PosXID()
{
    return floor(static_cast<int>(rect.center().x()+x())/20);
}
int Pacman::PosYID()
{
    return floor(static_cast<int>(rect.center().y()+y())/20);
}
