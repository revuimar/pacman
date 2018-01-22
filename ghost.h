#ifndef GHOST_H
#define GHOST_H
#define GHOST_WIDTH 20
#define GHOST_HEIGHT 20
#include "pacman.h"
#include "board.h"
#include <QGraphicsRectItem>
#include <QPoint>

class Board;
class Pacman;
class Wall;
class Ghost: public QGraphicsRectItem
{
public:
    enum aiType{Red,Orange,Cyan,Pink};
    enum ghostMoves{Up=0,Left=1,Right=2,Down=3,Pending,none};
    ghostMoves direction;
    ghostMoves previousDir;
    QRectF rect;
    bool outOfTheHouse;
private:
    Board* parent;

    bool scatterMode;
    bool isDead;
    aiType ghostName;
    bool isCollision();
public slots:
    void tryMoveGhost();
public:
    Ghost(int posx, int posy,aiType ghostType, Board* parent = 0);
    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);
    int PosTop();
    int PosBottom();
    int PosLeft();
    int PosRight();
    int PosYID();
    int PosXID();
    void setScatter(bool state){scatterMode = state;}
    void setLifeState(bool state){isDead = state;}
    void setGhostDirection();

    QVector<QPoint> possibleMoves();
    bool isGhostDead(){return isDead;}
    bool isScatter(){return scatterMode;}
    QPoint home(){return QPoint(14,14);}
    virtual QPoint ghostDestination(){return QPoint(0,0);}
};

#endif // GHOST_H
