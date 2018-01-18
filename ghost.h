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
class Ghost: public QGraphicsRectItem
{
public:
    enum aiType{Red,Orange,Cyan,Pink};
private:
    Board* parent;
    QRectF rect;
    bool scatterMode;
    bool isDead;
    aiType ghostName;
public:
    Ghost(int posx, int posy, aiType ghostName, Board* parent = 0);
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
    bool isGhostDead(){return isDead;}
    bool isScatter(){return scatterMode;}
    QPoint* ghostDestination(QVector<Ghost*> ghostBundle, Pacman* pacman);
};

#endif // GHOST_H
