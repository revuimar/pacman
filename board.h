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
#include "pacman.h"
#include "wall.h"
#include "ghost.h"
class Particle;
class Pacman;
class Wall;
class Blinky;
class Ghost;
class Board : public QGraphicsView
{
    Q_OBJECT

    QTimer *hightimer;
public:
    Board(QWidget* parent= 0);
    QGraphicsView* view;
    QGraphicsScene* scene;
    Pacman* pacman;
    QVector< QVector<Wall*>> wallMap;
    QBasicTimer timer;
    QVector<Ghost*> ghostContainer;
    enum { BoardWidth = 28, BoardHeight = 31};
    int score;

public slots:
    void start();
    void pause();
signals:
    void scoreChanged(int score);
    void levelChanged(int level);
private:

    int timeoutTime() { return 10; }

    void drawBoard();
    void timerEvent(QTimerEvent* event);
    bool pacmanOnTrackX();
    bool pacmanOnTrackY();
    Particle* item;
    void keyPressEvent(QKeyEvent *event);
    bool isStarted;
    bool isPaused;


    public:
    void deleteItem(int posx,int posy);
    QVector< QVector<Particle*> > map;
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
        {9,9,9,9,9,1,0,1,1,9,1,3,3,3,3,3,3,1,9,1,1,0,1,9,9,9,9,9},
        {1,1,1,1,1,1,0,1,1,9,1,9,9,9,9,9,9,1,9,1,1,0,1,1,1,1,1,1},
        {2,9,9,9,9,9,0,9,9,9,1,9,9,8,6,7,9,1,9,9,9,0,9,9,9,9,9,2},
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


};


#endif // BOARD_H
