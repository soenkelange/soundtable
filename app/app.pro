#-------------------------------------------------
#
# Project created by QtCreator 2015-01-14T13:01:54
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    a/projectafactory.cpp \
    b/projectbfactory.cpp \
    abstractprojectinfo.cpp \
    abstractprojectwidget.cpp \
    abstractprojectfactory.cpp \
    a/projectawidget.cpp \
    b/projectbwidget.cpp \
    b/card.cpp \
    b/widgets/videooutputtabwidget.cpp \
    b/widgets/videoplayercontrols.cpp \
    b/widgets/settingstabwidget.cpp \
    b/videoengine/videoplayer.cpp \
    b/soundengine/soundsource.cpp \
    b/soundengine/sound.cpp \
    b/soundengine/soundlistener.cpp \
    b/soundengine/soundengine.cpp

HEADERS  += mainwindow.h \
    a/projectafactory.h \
    b/projectbfactory.h \
    abstractprojectinfo.h \
    abstractprojectwidget.h \
    abstractprojectfactory.h \
    a/projectawidget.h \
    b/projectbwidget.h \
    b/card.h \
    b/widgets/videooutputtabwidget.h \
    b/widgets/videoplayercontrols.h \
    b/widgets/settingstabwidget.h \
    b/videoengine/videoplayer.h \
    b/soundengine/soundsource.h \
    b/soundengine/sound.h \
    b/soundengine/soundengine.h \
    b/soundengine/soundlistener.h

FORMS    += mainwindow.ui \
    a/projectawidget.ui \
    b/projectbwidget.ui \
    b/widgets/videooutputtabwidget.ui \
    b/widgets/videoplayercontrols.ui \
    b/widgets/settingstabwidget.ui

include(../libs/videoengine/videoengine.pri)



unix: LIBS += -L$$PWD/../../irrKlang/bin/macosx-gcc/ -lirrklang

INCLUDEPATH += $$PWD/../../irrKlang/include
DEPENDPATH += $$PWD/../../irrKlang/include
