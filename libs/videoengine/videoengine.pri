#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

INCLUDEPATH += $$PWD

SOURCES +=  $$PWD/videoengine.cpp \
    $$PWD/videowidget.cpp \
    $$PWD/videoformat.cpp

HEADERS  += $$PWD/videoengine.h \
    $$PWD/videowidget.h \
    $$PWD/cvmattoqimage.h \
    $$PWD/videoprocessor.h \
    $$PWD/videoformat.h

include(../../opencv.pri)
