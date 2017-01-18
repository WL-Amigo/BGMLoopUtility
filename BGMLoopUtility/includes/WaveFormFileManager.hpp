#ifndef WAVEFORMFILEMANAGER_HPP
#define WAVEFORMFILEMANAGER_HPP

#include "includes/WaveFormData.hpp"
#include "includes/WaveFormRW.hpp"
#include "includes/WaveFormFileType.hpp"

#include <QFile>

class WaveFormFileManager
{
private:
    WaveFormFileManager();
    ~WaveFormFileManager() = default;

public:
    WaveFormFileManager(const WaveFormFileManager&) = delete;
    WaveFormFileManager& operator=(const WaveFormFileManager&) = delete;
    WaveFormFileManager(WaveFormFileManager&&) = delete;
    WaveFormFileManager& operator=(WaveFormFileManager&&) = delete;

    static WaveFormFileManager& getInstance(){
        static WaveFormFileManager wffm;
        return wffm;
    }

    bool open(QString filePath);
    bool close();
    WaveFormFileType getFileType();
    WaveFormData* getWaveFormData();

private:
    QFile currentFile;
    WaveFormFileType currentFileType;
    WaveFormData* wfData;


};

#endif // WAVEFORMFILEMANAGER_HPP
