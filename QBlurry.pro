#-------------------------------------------------
#
# Project created by QtCreator 2015-01-30T22:59:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBlurry
TEMPLATE = app


CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    blurrer.cpp

HEADERS  += mainwindow.h \
    blurrer.h

FORMS    += mainwindow.ui
