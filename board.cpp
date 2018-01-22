#include "board.h"
#include "ui_mainwindow.h"
#include "particle.h"
#include "pacman.h"
#include "wall.h"
#include "blinky.h"
#include "inky.h"
#include "pinky.h"
#include "clyde.h"
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
    score = 0;
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
            case 6:
                item = nullptr;
                ghostContainer.push_back(new Inky(x*20,y*20,this));
                break;
            case 7:
                item = nullptr;
                ghostContainer.push_back(new Pinky(x*20,y*20,this));
                break;
            case 8:
                item = nullptr;
                ghostContainer.push_back(new Clyde(x*20,y*20,this));
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
    ghostContainer.push_back(new Blinky(14*20,11*20,this));
    for(auto i : ghostContainer) {
            scene->addItem(i);
    }
    scene->addItem(pacman);
}
void Board::deleteItem(int posx, int posy){
    delete map.at(posy).at(posx);
    map[posy].replace(posx,nullptr);
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
void Board::timerEvent(QTimerEvent *event)
{
    pacman->tryMove();
    ghostContainer.at(0)->tryMoveGhost();
    ghostContainer.at(1)->tryMoveGhost();
    ghostContainer.at(2)->tryMoveGhost();
    ghostContainer.at(3)->tryMoveGhost();
    timer.start(100,this);
    QWidget::timerEvent(event);
}
void Board::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused) {
        QWidget::keyPressEvent(event);
        return;
    }
    switch (event->key()) {
    case Qt::Key_Left:
        pacman->determineMove(Pacman::LEFT);
        break;
    case Qt::Key_Right:
        pacman->determineMove(Pacman::RIGHT);
        break;
    case Qt::Key_Down:
        pacman->determineMove(Pacman::DOWN);
        break;
    case Qt::Key_Up:
        pacman->determineMove(Pacman::UP);
        break;
    default:
        QWidget::keyPressEvent(event);
    }

}


