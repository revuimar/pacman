#-------------------------------------------------
#
# Project created by QtCreator 2018-01-06T11:27:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    particle.cpp \
    pacman.cpp \
    wall.cpp \
    ghost.cpp \
    blinky.cpp \
    inky.cpp \
    pinky.cpp \
    clyde.cpp

HEADERS  += mainwindow.h \
    board.h \
    particle.h \
    pacman.h \
    wall.h \
    ghost.h \
    blinky.h \
    inky.h \
    pinky.h \
    clyde.h

FORMS    += mainwindow.ui
CONFIG += c++11
