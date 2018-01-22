#ifndef PACMAN_H
#define PACMAN_H
#define PACMAN_WIDTH 20
#define PACMAN_HEIGHT 20
#include <QGraphicsRectItem>

class Board;
class Pacman: public QGraphicsRectItem
{
private:
    Board* parent;
    QRectF rect;
public:
    Pacman(int posx, int posy,Board* parent = 0);
    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);
    void tryMove();

    enum Direction {UP,DOWN,LEFT,RIGHT,NONE};
    Direction direction;
    Direction nextDirection;
    void determineMove(Direction selected);
    bool pacmanOnTrackX();
    bool pacmanOnTrackY();
    bool isCollision(Direction selected);
    int PosTop();
    int PosBottom();
    int PosLeft();
    int PosRight();
    int PosYID();
    int PosXID();
};

#endif // PACMAN_H
