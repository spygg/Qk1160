#-------------------------------------------------
#
# Project created by QtCreator 2016-07-07T10:38:40
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = gsnap
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lpng -ljpeg -lz -lm

target.path += /HNApp

INSTALLS += target
SOURCES += main.cpp \
    gsnap.c
