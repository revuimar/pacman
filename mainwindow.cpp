#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QStackedLayout>
#include <QMessageBox>
#include <iostream>
#include <QRect>
#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->quitButton, SIGNAL (released()), this, SLOT (handleQuit()));
    connect(ui->quitButton3, SIGNAL (released()), this, SLOT (handleQuit()));
    connect(ui->quitButton2, SIGNAL (released()), this, SLOT (handleQuitToMenu()));
    connect(ui->mainMenuButton, SIGNAL (released()), this, SLOT (handleQuitToMenu()));
    connect(ui->startButton, SIGNAL(released()), this, SLOT(handleStart()));
    connect(ui->pauseButton, SIGNAL (released()), this, SLOT (handlePause()));
    connect(ui->lcdNumber_2, SIGNAL(scoreChanged(int)), this, SLOT(display(int)));
    ui->stackedWidget->setCurrentIndex(0);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleQuit()
{
    QCoreApplication::exit();
}
void MainWindow::handleQuitToMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::handleStart()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->board->start();
}
void MainWindow::handlePause()
{
    ui->board->pause();
}
