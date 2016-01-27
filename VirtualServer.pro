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

include(VirtualServer.pri)


QMAKE_CXXFLAGS += -std=c++11



