#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T22:15:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VirtualServer
TEMPLATE = app

INCLUDEPATH += $(QT_DIR)/include/QtCore
INCLUDEPATH += ./gui/core
INCLUDEPATH += ./gui
INCLUDEPATH += ./gui/forms
INCLUDEPATH += ./gui/core/form
INCLUDEPATH += ./gui/core/viewmodel
INCLUDEPATH += ./gui/core/controls
INCLUDEPATH +=./capture
INCLUDEPATH +=./core/api

include(VirtualServer.pri)

LIBS += -lpcap 
QMAKE_CXXFLAGS += -std=c++11


Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
