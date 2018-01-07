#include "board.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QWidget>
#include <QFrame>
#include <QRect>
#include <QPainter>
Board::Board(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    //fikin catch this frame in mainwindow constructor ;)
    isStarted = false;
    isPaused = false;
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect = QRect(290, 20, 70, 40);
    painter.drawText(rect, Qt::AlignCenter,"Data");
    painter.drawRect(rect);
}
