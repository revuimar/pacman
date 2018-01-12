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
Board::Board(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);
    drawBoard();
}
void Board::drawBoard()
{

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
            default:
                item = nullptr;
                break;
            }
            map[y].push_back(item);
        }
    }
    for(auto i : map) {
            for(auto j : i) {
                scene->addItem(j);
            }
        }
}
void Board::deleteItem(int posx, int posy){
    delete map.at(posy).at(posx);
    map[posy].replace(posx,nullptr);
    update();
}
