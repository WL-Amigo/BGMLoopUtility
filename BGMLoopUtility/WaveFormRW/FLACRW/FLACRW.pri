QT += core

INCLUDEPATH += ../ \
    $$PWD/libflac-include

LIBS:UNIX += -lflac8

HEADERS += \
    $$PWD/FLACRW.hpp

SOURCES += \
    $$PWD/FLACRW.cpp
