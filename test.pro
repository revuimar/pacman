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
    particle.cpp

HEADERS  += mainwindow.h \
    board.h \
    particle.h

FORMS    += mainwindow.ui
CONFIG += c++11
