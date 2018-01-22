#include "pacman.h"
#include "ui_mainwindow.h"
#include "board.h"
#include <QApplication>
#include <QPen>
#include <QSize>
#include <QBrush>
#include <QRect>
#include <QPainter>
#include <QTimer>
#include <iostream>

Pacman::Pacman(int posx, int posy, Board* parent)
    :QGraphicsRectItem(posx,posy,PACMAN_WIDTH,PACMAN_HEIGHT)
{
    this->parent = parent;
    rect = QRect(posx,posy,PACMAN_WIDTH,PACMAN_HEIGHT);
    direction = NONE;
    nextDirection = NONE;
    canIEat = false;

    t = new QTimer();
    t->setInterval(5000);

    connect(t,SIGNAL(timeout()),this,SLOT(reset()));
}
void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem* /* unused */, QWidget* /* unused */)
{
    painter->setBrush(QBrush(QColor("yellow")));
    painter->drawEllipse(rect);
}


void Pacman::tryMove()
{
        switch (direction) {
        case LEFT:
            if(!isCollision(LEFT))
            {
                moveBy(-20,0);
            }
            break;
        case RIGHT:
            if(!isCollision(RIGHT)){
                moveBy(20,0);
            }
            break;
        case UP:
            if(!isCollision(UP)){
                moveBy(0,-20);
            }
            break;
        case DOWN:
            if(!isCollision(DOWN)){
                moveBy(0,20);
            }
            break;
        default:
            break;
        }
        if(!isCollision(nextDirection)){
            direction = nextDirection;
        }
        if(Particle::isThereDot(parent->map.at(PosYID()).at(PosXID()))){
            parent->deleteItem(PosXID(),PosYID());
            parent->score+=10;
            emit parent->scoreChanged(parent->score);
        }
        if(Particle::isTherePellet(parent->map.at(PosYID()).at(PosXID()))){
            parent->deleteItem(PosXID(),PosYID());
            parent->score+=50;
            emit parent->scoreChanged(parent->score);
            canIEat = true;
            t->start();
        }

}


bool Pacman::isCollision(Direction selected)
{
    int pacmanXID = PosXID();
    int pacmanYID = PosYID();
    switch(selected){
        case LEFT:
            if(parent->wallMap.at(pacmanYID).at(pacmanXID-1)->isHereMapBoundary())
            {
                return true;
            }
            break;
        case RIGHT:
            if(parent->wallMap.at(pacmanYID).at(pacmanXID+1)->isHereMapBoundary())
            {
                return true;
            }
            break;
        case UP:
            if(parent->wallMap.at(pacmanYID-1).at(pacmanXID)->isHereMapBoundary())
            {
            return true;
            }
            break;
        case DOWN:
            if(parent->wallMap.at(pacmanYID+1).at(pacmanXID)->isHereMapBoundary())
            {
            return true;
            }
            break;
        case NONE:
            return true;
            break;
            default: break;
    }
    return false;
}
void Pacman::determineMove(Direction selectedDir)
{
    if(isCollision(selectedDir))
    {
        nextDirection = selectedDir;
    }
    else
    {
        direction = selectedDir;
        nextDirection = NONE;
    }

}
void Pacman::reset() {
    canIEat = false;
    t->stop();
}

bool Pacman::pacmanOnTrackX()
{
    return PosTop()%20 == 0;
}
bool Pacman::pacmanOnTrackY()
{
    return PosLeft()%20 == 0;
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
