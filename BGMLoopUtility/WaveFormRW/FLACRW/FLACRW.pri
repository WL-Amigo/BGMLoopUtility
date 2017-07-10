QT += core

INCLUDEPATH += ../ \
    $$PWD/libflac-include

unix:LIBS += -lFLAC -lFLAC++

HEADERS += \
    $$PWD/FLACRW.hpp

SOURCES += \
    $$PWD/FLACRW.cpp
