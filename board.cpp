#include "board.h"
#include "ui_mainwindow.h"
#include "particle.h"
#include <QCoreApplication>
#include <QWidget>
#include <QPainter>
#include <QRect>
#include <QGraphicsRectItem>
#include <QDebug>
#include <iostream>
#include <QThread>

Board::Board(QWidget *parent)
    : QGraphicsView(parent)
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
            case 1:
                item = new Particle(x*20,y*20,Particle::Rect,this);
                break;
            case 0:
                item = new Particle(x*20,y*20,Particle::Dot,this);
                break;
            case 4:
                item = new Particle(x*20,y*20,Particle::PacDot,this);
                break;
            case 5:
                item = nullptr;
                pacman = new Particle(x*20,y*20,Particle::PacMan,this);;
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
    int incrX=0,incrY=0;
    bool wallNotColided = true;
        switch (direction) {
        case LEFT:
            if(!Particle::isMapBoundary(map.at(floor(pacman->PosTop()/20)).at(floor(pacman->PosLeft()/20)-1)))
            {
                pacman->moveBy(-5,0);
            }
            else{
                wallNotColided = false;
                nextEvent = false;
            break;
        case RIGHT:
            if(!Particle::isMapBoundary(map.at(floor(pacman->PosTop()/20)).at(floor(pacman->PosRight()/20)))){
                pacman->moveBy(5,0);
            }
            else{
                wallNotColided = false;
                nextEvent = false;
            }
            break;
        case UP:
            if(!Particle::isMapBoundary(map.at(floor(pacman->PosTop()/20)-1).at(floor(pacman->PosLeft()/20)))){
                pacman->moveBy(0,-5);
            }
            else{
                wallNotColided = false;
                nextEvent = false;
            }
            break;
        case DOWN:
            if(!Particle::isMapBoundary(map.at(floor(pacman->PosBottom()/20)).at(floor(pacman->PosLeft()/20)))){
                pacman->moveBy(0,5);
            }
            else{
                wallNotColided = false;
                nextEvent = false;
            }
            break;
        default:
            break;
        }
        }
        if(Particle::isThereDot(map.at(floor(pacman->PosTop()/20)).at(floor(pacman->PosLeft()/20)))){
            deleteItem(floor(pacman->PosLeft()/20),floor(pacman->PosTop()/20));
            score+=10;
        }
        if(Particle::isTherePellet(map.at(floor(pacman->PosTop()/20)).at(floor(pacman->PosLeft()/20)))){
            deleteItem(floor(pacman->PosLeft()/20),floor(pacman->PosTop()/20));
            score+=50;
        }

        std::cerr<<"PosAXID posx:"<<pacman->PosLeft()<<" posy:"<<pacman->PosTop()<<"lol"<<endl;
        std::cerr<<"Posx&y posx:"<<pacman->x()<<" posy:"<<pacman->y()<<"lol"<<endl;
        repaint();

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
