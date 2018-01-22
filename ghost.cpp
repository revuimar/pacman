#include "ghost.h"
#include <QGraphicsRectItem>
#include "pacman.h"
#include "ui_mainwindow.h"
#include "board.h"
#include "wall.h"
#include <QPen>
#include <QSize>
#include <QBrush>
#include <QRect>
#include <QPainter>
#include <iostream>


Ghost::Ghost(int posx, int posy, aiType ghostType, Board* parent)
    :QGraphicsRectItem(posx,posy,GHOST_WIDTH,GHOST_HEIGHT), ghostName(ghostType)
{
    this->parent = parent;
    rect = QRect(posx,posy,PACMAN_WIDTH,PACMAN_HEIGHT);
    scatterMode = false;
    isDead = false;
    direction = Left;
    outOfTheHouse = true;
}
void Ghost::setGhostDirection()
{
    int numberOfmoves = 0;
    if(direction == Pending){
        QVector<QPoint> moves = possibleMoves();
        for(int i = 0; i < 4; i++){
            if(!moves.at(i).isNull())
            {
                numberOfmoves++;
            }
        }
        QPoint dst = ghostDestination();
        if(numberOfmoves == 1)
        {
            for(int i = 0; i < 4; i++){
                if(!moves.at(i).isNull())
                {
                    direction = static_cast<ghostMoves>(i);
                    return;
                }
            }
        }
        else
        {
            int rateX = abs(dst.x()-PosXID());
            int rateY = abs(dst.y()-PosYID());
            if(!moves.at(Left).isNull() && !moves.at(Right).isNull())
            {
                if(dst.x() > PosXID())
                    direction = Right;
                else
                    direction = Left;
                return;
            }
            else if(!moves.at(Up).isNull() && !moves.at(Down).isNull())
            {
                if(dst.y() > PosYID())
                    direction = Down;
                else
                    direction = Up;
                return;
            }
            else if(!moves.at(Up).isNull() && !moves.at(Left).isNull())
            {
                if(rateX > rateY )
                    direction = Up;
                else
                    direction = Left;
                return;
            }
            else if(!moves.at(Up).isNull() && !moves.at(Right).isNull())
            {
                if(rateX > rateY)
                    direction = Up;
                else
                    direction = Right;
                return;
            }
            else if(!moves.at(Down).isNull() && !moves.at(Left).isNull())
            {
                if(rateX > rateY)
                    direction = Down;
                else
                    direction = Left;
                return;
            }
            else if(!moves.at(Down).isNull() && !moves.at(Right).isNull())
            {
                if(rateX > rateY)
                    direction = Down;
                else
                    direction = Right;
                return;
            }
        }
    }
}
QVector<QPoint> Ghost::possibleMoves()
{
    QVector<QPoint> destVec;
    int ghostPosXID = PosXID();
    int ghostPosYID = PosYID();
    for(int i = 0;i<4;i++){
       destVec.push_back(QPoint(0,0));
    }
    if(!(parent->wallMap.at(ghostPosYID).at(ghostPosXID-1)->isHereMapBoundary()))
        destVec.replace(Left, QPoint(ghostPosXID-1,ghostPosYID));
    if(!(parent->wallMap.at(ghostPosYID).at(ghostPosXID+1)->isHereMapBoundary()))
        destVec.replace(Right, QPoint(ghostPosXID+1,ghostPosYID));
    if(!(parent->wallMap.at(ghostPosYID-1).at(ghostPosXID)->isHereMapBoundary()))
        destVec.replace(Up, QPoint(ghostPosXID,ghostPosYID-1));
    if(!(parent->wallMap.at(ghostPosYID+1).at(ghostPosXID))->isHereMapBoundary())
        destVec.replace(Down, QPoint(ghostPosXID,ghostPosYID+1));
    destVec.replace(previousDir, QPoint(0,0));
    return destVec;
}
bool Ghost::isCollision()
{
    int ghostPosXID = PosXID();
    int ghostPosYID = PosYID();
    if(outOfTheHouse && parent->wallMap.at(ghostPosYID-1).at(ghostPosXID)->isHereMapBoundary())
    {
        outOfTheHouse = false;
        return false;
    }
    switch(direction)
    {
        case Up:
            if(parent->wallMap.at(ghostPosYID-1).at(ghostPosXID)->isHereMapBoundary())
                return true;
            break;
        case Down:
            if(parent->wallMap.at(ghostPosYID+1).at(ghostPosXID)->isHereMapBoundary())
                return true;
            break;
        case Left:
            if(parent->wallMap.at(ghostPosYID).at(ghostPosXID-1)->isHereMapBoundary())
                return true;
            break;
        case Right:
            if(parent->wallMap.at(ghostPosYID).at(ghostPosXID+1)->isHereMapBoundary())
                return true;
            break;
        default:
            break;
    }
    return false;
}

void Ghost::tryMoveGhost()
{
    setGhostDirection();
    if(!isCollision()){
    switch (direction) {
        case Up:
            moveBy(0,-20);
            break;
        case Left:
            moveBy(-20,0);
            break;
        case Right:
            moveBy(20,0);
            break;
        case Down:
            moveBy(0,20);
            break;
        default:
            break;
    }
    }
    else{
        if(direction == Left)
            previousDir = Right;
        else if(direction == Right)
            previousDir = Left;
        else if(direction == Up)
            previousDir = Down;
        else if(direction == Down)
            previousDir = Up;
        direction = Pending;
    }
}
void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem* /* unused */, QWidget* /* unused */)
{
    QPainterPath path;
    path.moveTo(rect.left() + (rect.width() / 2), rect.top());
    path.lineTo(rect.bottomLeft());
    path.lineTo(rect.bottomRight());
    path.lineTo(rect.left() + (rect.width() / 2), rect.top());

    switch (ghostName) {
    case Red:
        painter->fillPath(path,QBrush(QColor("red")));
        break;
    case Pink:
        painter->fillPath(path,QBrush(QColor("pink")));
        break;
    case Cyan:
        painter->fillPath(path,QBrush(QColor("cyan")));
        break;
    case Orange:
        painter->fillPath(path,QBrush(QColor("orange")));
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

