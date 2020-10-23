#-------------------------------------------------
#
# Project created by adk 2011-09-20T20:00:17
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += core
QT       += widgets

CONFIG += c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GNULOCSYS
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp


HEADERS  += mainwindow.h\
        common.h

FORMS    += mainwindow.ui


