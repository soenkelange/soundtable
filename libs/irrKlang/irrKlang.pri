message(Include irrKlang library from $$PWD)

macx: LIBS += -L$$PWD/bin/macosx-gcc/ -lirrklang

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/irrKlang/include
