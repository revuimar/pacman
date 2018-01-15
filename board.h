#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QBasicTimer>
#include <QKeyEvent>
#include "particle.h"
class Particle;
class Board : public QGraphicsView
{
public:
    Board(QWidget* parent= 0);
    QGraphicsView* view;
    QGraphicsScene* scene;
    enum { BoardWidth = 28, BoardHeight = 31};
    enum Direction {UP,DOWN,LEFT,RIGHT};

public slots:
    void start();
    void pause();
signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void deleteItem(int posx,int posy);
private:

    int timeoutTime() { return 10; }
    Direction direction;
    void drawBoard();
    void timerEvent(QTimerEvent* event);
    void keyPressEvent(QKeyEvent *event);
    Particle* item;
    Particle* pacman;
    bool isStarted;
    bool isPaused;
    bool nextEvent;
    int score;
    QBasicTimer timer;
    void tryMove();
    std::vector<std::vector<int> > boardMap ={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,4,1,9,9,1,0,1,9,9,9,1,0,1,1,0,1,9,9,9,1,0,1,9,9,1,4,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,0,1,1,1,1,1,9,1,1,9,1,1,1,1,1,0,1,1,1,1,1,1},
        {9,9,9,9,9,1,0,1,1,1,1,1,9,1,1,9,1,1,1,1,1,0,1,9,9,9,9,9},
        {9,9,9,9,9,1,0,1,1,9,9,9,9,9,9,9,9,9,9,1,1,0,1,9,9,9,9,9},
        {9,9,9,9,9,1,0,1,1,9,1,1,1,3,3,1,1,1,9,1,1,0,1,9,9,9,9,9},
        {1,1,1,1,1,1,0,1,1,9,1,9,9,9,9,9,9,1,9,1,1,0,1,1,1,1,1,1},
        {2,9,9,9,9,9,0,9,9,9,1,9,9,9,9,9,9,1,9,9,9,0,9,9,9,9,9,2},
        {1,1,1,1,1,1,0,1,1,9,1,9,9,9,9,9,9,1,9,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,9,1,1,1,1,1,1,1,1,9,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,9,9,9,9,9,9,9,9,9,9,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,9,1,1,1,1,1,1,1,1,9,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,9,1,1,1,1,1,1,1,1,9,1,1,0,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,4,0,0,1,1,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,1,1,0,0,4,1},
        {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
        {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
        //0-empty
        //1-wall
        //2-portal
        //3-ghost door
    QVector< QVector<Particle*> > map;
};


#endif // BOARD_H
