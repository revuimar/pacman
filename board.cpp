#include "board.h"
#include "ui_mainwindow.h"
#include "particle.h"
#include "pacman.h"
#include "wall.h"
#include <QCoreApplication>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QRect>
#include <QGraphicsRectItem>
#include <QDebug>
#include <iostream>
#include <QThread>

Board::Board(QWidget *parent): QGraphicsView(parent)
{

    isPaused = false;
    isStarted = false;

    start();
}
void Board::drawBoard()
{
    scene = new QGraphicsScene();
    setScene(scene);
    for(int y = 0; y < BoardHeight ;y++){
        map.push_back( QVector<Particle*>() );
        for(int x = 0; x < BoardWidth ;x++){
            switch(boardMap.at(y).at(x))
            {
            case 0:
                item = new Particle(x*20,y*20,Particle::Dot,this);
                break;
            case 4:
                item = new Particle(x*20,y*20,Particle::PacDot,this);
                break;
            case 5:
                item = nullptr;
                pacman = new Pacman(x*20,y*20,this);
                break;
            default:
                item = nullptr;
                break;
            }
            map[y].push_back(item);
        }
    }
    for(auto i : map) {
            for(auto j : i) {
                if(j == nullptr) continue;
                scene->addItem(j);
            }
        }
    wallMap = Wall::wallInitialiser(&boardMap,this);
    for(auto i : wallMap) {
        for(auto j : i) {
            if(j == nullptr) continue;
            scene->addItem(j);
        }
    }
    scene->addItem(pacman);
}
void Board::deleteItem(int posx, int posy){
    delete map.at(posy).at(posx);
    map[posy].replace(posx,nullptr);
}
void Board::timerEvent(QTimerEvent *event)
{
    QWidget::timerEvent(event);
}

void Board::start()
{
    if (isPaused)
        return;
    isStarted = true;
    score = 0;

    drawBoard();
    hightimer = new QTimer(this);
    hightimer->start();
    timer.start(timeoutTime(), this);
}

void Board::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    update();
}
void Board::tryMove()
{
    bool wallNotColided = true;
        switch (direction) {
        case LEFT:
            pacman->moveBy(-5,0);
            if(isCollision())
            {
                pacman->moveBy(5,0);
                wallNotColided = false;
                nextEvent = false;
            }
            break;
        case RIGHT:
            pacman->moveBy(5,0);
            if(isCollision()){
                pacman->moveBy(-5,0);
                wallNotColided = false;
                nextEvent = false;
            }
            break;
        case UP:
            pacman->moveBy(0,-5);
            if(isCollision()){
                pacman->moveBy(0,5);
                wallNotColided = false;
                nextEvent = false;
            }
            break;
        case DOWN:
            pacman->moveBy(0,5);
            if(isCollision()){
                pacman->moveBy(0,-5);
                wallNotColided = false;
                nextEvent = false;
            }
            break;
        default:
            break;
        }
        if(Particle::isThereDot(map.at(pacman->PosYID()).at(pacman->PosXID()))){
            deleteItem(pacman->PosXID(),pacman->PosYID());
            score+=10;
        }
        if(Particle::isTherePellet(map.at(pacman->PosYID()).at(pacman->PosXID()))){
            deleteItem(pacman->PosXID(),pacman->PosYID());
            score+=50;
        }
        repaint();

}
bool Board::isCollision()
{
    int pacmanXID = pacman->PosXID();
    int pacmanYID = pacman->PosYID();
        switch(direction){
            case LEFT:
                if(!pacmanOnTrackX()) return true;
                if(wallMap.at(pacmanYID).at(pacmanXID-1)->isHereMapBoundary())
                {
                    if(pacman->PosLeft() < wallMap.at(pacmanYID).at(pacmanXID-1)->PosRight()){
                        return true;
                    }
                }
                return false;
            case RIGHT:
                if(!pacmanOnTrackX()) return true;
                if(wallMap.at(pacmanYID).at(pacmanXID+1)->isHereMapBoundary())
                {
                    if(pacman->PosRight() > wallMap.at(pacmanYID).at(pacmanXID+1)->PosLeft()){
                        return true;
                    }
                }
                return false;
            case UP:
                if(!pacmanOnTrackY()) return true;
                if(wallMap.at(pacmanYID-1).at(pacmanXID)->isHereMapBoundary())
                {
                    if(pacman->PosTop() < wallMap.at(pacmanYID-1).at(pacmanXID)->PosBottom()){
                        return true;
                    }
                }
                return false;
            case DOWN:
                if(!pacmanOnTrackY()) return true;
                if(wallMap.at(pacmanYID+1).at(pacmanXID)->isHereMapBoundary())
                {
                    if(pacman->PosBottom() > wallMap.at(pacmanYID+1).at(pacmanXID)->PosTop()){
                        return true;
                    }
                }
                return false;
            default: break;
        }
    return false;
}
bool Board::pacmanOnTrackX()
{
    return pacman->PosTop()%20 == 0;
}
bool Board::pacmanOnTrackY()
{
    return pacman->PosLeft()%20 == 0;
}

void Board::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused) {
        QWidget::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        direction = LEFT;
        nextEvent = true;
        break;
    case Qt::Key_Right:
        direction = RIGHT;
        nextEvent = true;
        break;
    case Qt::Key_Down:
        direction = DOWN;
        nextEvent = true;
        break;
    case Qt::Key_Up:
        direction = UP;
        nextEvent = true;

        break;
    default:
        QWidget::keyPressEvent(event);
    }
    tryMove();

}
