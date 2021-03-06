#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void handleQuit();
    void handleStart();
    void handleQuitToMenu();
    void handlePause();
private:
    QGraphicsScene* scene;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
