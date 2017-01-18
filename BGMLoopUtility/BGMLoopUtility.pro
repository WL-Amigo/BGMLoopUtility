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
    src/WaveFormFileManager.cpp \
    src/WaveFormData.cpp \
    src/WaveFormRW.cpp

HEADERS  += includes/MainWindow.hpp \
    includes/WaveFormFileManager.hpp \
    includes/WaveFormData.hpp \
    includes/WaveFormRW.hpp \
    includes/WaveFormFileType.hpp

FORMS    += forms/MainWindow.ui

RESOURCES += \
    resources/resources.qrc
