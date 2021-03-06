#ifndef WALL_H
#define WALL_H
#define WALL_WIDTH 20
#define WALL_HEIGHT 20
#include "board.h"
#include <QGraphicsRectItem>
#include <QVector>

class Board;
class Wall: public QGraphicsRectItem
{
private:
    Board* parent;
    QRectF rect;
public:
    enum wallType{HOUSE,WALL};
    wallType wallsType;
    Wall(int posx, int posy,wallType chosenWallType,Board* parent = 0);
    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);

    int PosTop();
    int PosBottom();
    int PosLeft();
    int PosRight();
    int PosYID();
    int PosXID();
    static QVector<QVector<Wall*>>
           wallInitialiser(std::vector<std::vector<int>>* baseMap, Board* parent = 0);
    bool isHereMapBoundary(){return !(this == nullptr);}
};

#endif // WALL_H
