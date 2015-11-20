#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T18:30:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCPStub
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        ../STRUCTURE/database_structure.cpp \
        ../STRUCTURE/rawdata_structure.cpp \
        ../STRUCTURE/scenario_struct.cpp

HEADERS  += mainwindow.h \


FORMS    += mainwindow.ui
