#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include <QFrame>
class Board : public QFrame
{
    Q_OBJECT

public:
    Board(QWidget *parent = 0);

public slots:
    //void start();
    //void pause();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
private:
    enum { BoardWidth = 28, BoardHeight = 22};
    /*
    enum { PacMan_posx, PacMan_posy};
    enum { Pinky_posx, Pinky_posy}; // pink 4 tiles ahead of pacman
    enum { Blinky_posx, Blinky_posy};//always chases pacman
    enum { Inky_posx, Inky_posy}; // blue chases after eating 30 dots 2 of vector from blinky position to 2 tiles ahead of pacman
    enum { Clyde_posx, Clyde_posy};//orange leaves house after pacman eating 3 dots when further than 8 tiles from pacman he has blinky mode else he tries to reach left bottom corner
    */
    int tileWidth(){return contentsRect().width()/BoardWidth;}
    int tileHeight(){return contentsRect().height()/BoardHeight;}
    bool isStarted;
    bool isPaused;


};


#endif // BOARD_H
