#include "ghost.h"
#include <QGraphicsRectItem>
#include "pacman.h"
#include "ui_mainwindow.h"
#include "board.h"
#include <QPen>
#include <QSize>
#include <QBrush>
#include <QRect>
#include <QPainter>

Ghost::Ghost(int posx, int posy, aiType ghostType, Board* parent)
    :QGraphicsRectItem(posx,posy,GHOST_WIDTH,GHOST_HEIGHT), ghostName(ghostType)
{
    this->parent = parent;
    rect = QRect(posx,posy,PACMAN_WIDTH,PACMAN_HEIGHT);
    scatterMode = false;
    isDead = false;
}
void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (ghostName) {
    case Red:
        painter->setBrush(QBrush(QColor("red")));
        break;
    case Pink:
        painter->setBrush(QBrush(QColor("pink")));
        break;
    case Cyan:
        painter->setBrush(QBrush(QColor("cyan")));
        break;
    case Orange:
        painter->setBrush(QBrush(QColor("orange")));
        break;
    default:
        break;
    }
    painter->drawEllipse(rect);
}
QPoint* Ghost::ghostDestination(QVector<Ghost*> ghostBundle, Pacman* pacman)
{
    switch (ghostName) {
    case Red:
        return new QPoint(pacman->PosXID(),pacman->PosYID());
        break;
    case Pink:
        break;
    case Cyan:
        break;
    case Orange:
        break;
    default:
        break;
    }
}

int Ghost::PosLeft()
{
    return (static_cast<int>(rect.left()+x()));
}
int Ghost::PosTop()
{
    return (static_cast<int>(rect.top()+y()));
}
int Ghost::PosBottom()
{
    return (static_cast<int>(rect.bottom()+y()));
}
int Ghost::PosRight()
{
    return (static_cast<int>(rect.right()+x()));
}
int Ghost::PosXID()
{
    return floor(static_cast<int>(rect.center().x()+x())/20);
}
int Ghost::PosYID()
{
    return floor(static_cast<int>(rect.center().y()+y())/20);
}

