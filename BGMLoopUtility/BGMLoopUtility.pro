#-------------------------------------------------
#
# Project created by QtCreator 2017-01-18T13:32:44
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BGMLoopUtility
TEMPLATE = app

CONFIG += c++11


SOURCES += src/main.cpp\
        src/MainWindow.cpp \
    #src/WaveFormRW.cpp \
    src/AcceptDropLabel.cpp \
    src/LoopPointDetector.cpp \
    src/LoopPointDetectorGUI.cpp \
    src/WaveFormViewerBase.cpp \
    src/WaveFormViewerSingle.cpp \

HEADERS  += includes/MainWindow.hpp \
    #includes/WaveFormRW.hpp \
    includes/AcceptDropLabel.hpp \
    includes/LoopPointDetector.hpp \
    includes/LoopPointDetectorGUI.hpp \
    includes/WaveFormViewerBase.hpp \
    includes/WaveFormViewerSingle.hpp \

FORMS    += forms/MainWindow.ui \
    forms/LoopPointDetectorGUI.ui

RESOURCES += \
    resources/resources.qrc

include(WaveFormRW/WaveFormRW.pri);
include(Core/Core.pri);
