#include "wall.h"
#include "ui_mainwindow.h"
#include "board.h"
#include <QPen>
#include <QSize>
#include <QBrush>
#include <QRect>
#include <QPainter>
#include <QDebug>
#include <QVector>
Wall::Wall(int posx, int posy, Board* parent)
    :QGraphicsRectItem(posx,posy,WALL_WIDTH,WALL_HEIGHT)
{
    this->parent = parent;
    rect = QRect(posx,posy,20,20);
}
void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor("blue")));
    painter->drawRect(rect);
}

QVector<QVector<Wall*>> Wall::wallInitialiser(std::vector<std::vector<int>>* baseMap, Board* parent)
{
    QVector<QVector<Wall*>> map;
    for(int y = 0; y < Board::BoardHeight ;y++)
    {
        map.push_back( QVector<Wall*>() );
        for(int x = 0; x < Board::BoardWidth ;x++)
        {
            if(baseMap->at(y).at(x) == 1)
            {
                map[y].push_back(new Wall(x*WALL_WIDTH,y*WALL_HEIGHT,parent));
            }
            else
            {
                map[y].push_back(nullptr);
            }
        }
    }
    return map;
}
int Wall::PosLeft()
{
    return (static_cast<int>(rect.left()+x()));
}
int Wall::PosTop()
{
    return (static_cast<int>(rect.top()+y()));
}
int Wall::PosBottom()
{
    return (static_cast<int>(rect.bottom()+y()));
}
int Wall::PosRight()
{
    return (static_cast<int>(rect.right()+x()));
}
int Wall::PosXID()
{
    return floor(static_cast<int>(rect.center().x()+x())/20);
}
int Wall::PosYID()
{
    return floor(static_cast<int>(rect.center().y()+y())/20);
}
