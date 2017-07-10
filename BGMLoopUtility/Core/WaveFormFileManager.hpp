#ifndef WAVEFORMFILEMANAGER_HPP
#define WAVEFORMFILEMANAGER_HPP

#include "Core/WaveFormData.hpp"
#include "Core/WaveFormFileType.hpp"
#include "includes/WaveFormRW.hpp"

#include <QFile>

class WaveFormFileManager {
private:
    WaveFormFileManager();
    ~WaveFormFileManager() = default;

public:
    WaveFormFileManager(const WaveFormFileManager&) = delete;
    WaveFormFileManager& operator=(const WaveFormFileManager&) = delete;
    WaveFormFileManager(WaveFormFileManager&&) = delete;
    WaveFormFileManager& operator=(WaveFormFileManager&&) = delete;

    static WaveFormFileManager& getInstance() {
        static WaveFormFileManager wffm;
        return wffm;
    }

    bool open(QString filePath);
    bool close();
    WaveFormFileType getFileType();
    WaveFormData* getWaveFormData();
    bool isOpened();
    QString getLoopInfoFileName();

private:
    QFile currentFile;
    WaveFormFileType currentFileType;
    WaveFormData* wfData;
    QString loopInfoFileName;
};

#endif  // WAVEFORMFILEMANAGER_HPP
