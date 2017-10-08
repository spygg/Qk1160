include(../tableprinter.pri)

MOC_DIR = tmp/moc
UI_DIR = tmp/ui
OBJECTS_DIR = tmp/obj
RCC_DIR = tmp/rcc

LANGUAGE = C++
QT +=  core gui

CONFIG += qt debug warn_on staticlib
CONFIG -= release shared

DEPENDPATH    += ../src ../forms
INCLUDEPATH    += ../src ./  $(QTDIR)/include

RESOURCES += ../tableprinterresource.qrc

DESTDIR   = lib
TEMPLATE     = lib
TARGET=tableprinter

#win32: QMAKE_CXXFLAGS_MT_DLL+=
