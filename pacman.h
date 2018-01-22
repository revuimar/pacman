#ifndef PACMAN_H
#define PACMAN_H
#define PACMAN_WIDTH 20
#define PACMAN_HEIGHT 20
#include <QGraphicsRectItem>
#include <QTimer>

class Board;
class Pacman: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    Board* parent;
    QRectF rect;
public slots:
    void reset();
public:
    Pacman(int posx, int posy,Board* parent = 0);
    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget);
    void tryMove();
    bool canIEat;

    QTimer* t;
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
