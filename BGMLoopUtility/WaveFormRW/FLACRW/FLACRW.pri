QT += core

INCLUDEPATH += ../ \
    $$PWD/libflac-include

unix:LIBS += -lFLAC -lFLAC++
win32:PRE_TARGETDEPS += $$PWD/../../platform/windows/lib/libFLAC.dll.a \
    $$PWD/../../platform/windows/lib/libFLAC++.dll.a
win32:LIBS += -L$$PWD/../../platform/windows/bin -lFLAC-8 -lFLAC++-6

HEADERS += \
    $$PWD/FLACRW.hpp

SOURCES += \
    $$PWD/FLACRW.cpp

DEFINES += BGMLU_ENABLE_FLAC
