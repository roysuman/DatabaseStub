#-------------------------------------------------
#
# Project created by QtCreator 2016-01-31T20:53:01
#
#-------------------------------------------------

QT       += core
QT += xml

QT       -= gui

TARGET = xmlparser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
SOURCES +=../../core/xmlparser/parser.cpp
HEADERS +=../../core/xmlparser/parser.h
SOURCES +=../../core/xmlparser/parseringbuffer.cpp
HEADERS +=../../core/xmlparser/parseringbuffer.h
SOURCES +=../../core/xmlparser/parsermanager.cpp
HEADERS +=../../core/xmlparser/parsermanager.h
HEADERS +=../../core/api/ringbuffer.h
SOURCES +=../../core/api/ringbuffer.cpp
HEADERS +=../../core/api/apihelper.h

QMAKE_CXXFLAGS += -std=c++11
