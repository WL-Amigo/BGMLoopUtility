QT += core

CONFIG += c++11

HEADERS += \
    $$PWD/WaveFormRW.hpp

SOURCES += \
    $$PWD/WaveFormRW.cpp

include(RIFFWaveRW/RIFFWaveRW.pri);
include(FLACRW/FLACRW.pri);
