#ifndef WAVEFORMRW_HPP
#define WAVEFORMRW_HPP

#include <QFile>
#include <QMap>
#include "Core/WaveFormData.hpp"
#include "Core/WaveFormFileType.hpp"

class IWaveFormRW {
public:
    IWaveFormRW();
    virtual ~IWaveFormRW();

    virtual bool test(QFile& file) = 0;
    virtual WaveFormData* read(QFile& file) = 0;
};

class WaveFormRW {
public:
    WaveFormRW() {}

    static WaveFormFileType test(QFile& wfFile);
    static WaveFormData* read(QFile& wfFile);
    static bool write(QFile& destFile, WaveFormFileType fileType,
                      WaveFormData& wfData);

private:
    static QMap<WaveFormFileType, IWaveFormRW*> s_fileTypeToRWer;
};

#endif  // WAVEFORMRW_HPP
