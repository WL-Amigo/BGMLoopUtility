#ifndef WAVEFORMRW_HPP
#define WAVEFORMRW_HPP

#include "includes/WaveFormData.hpp"
#include "includes/WaveFormFileType.hpp"

#include <QFile>


class WaveFormRW
{
public:
    WaveFormRW();

    static WaveFormFileType test(QFile& wfFile);
    static WaveFormData* read(QFile& wfFile);
    static bool write(QFile& destFile, WaveFormFileType fileType, WaveFormData& wfData);

private:
    // for RIFF Wave file
    static bool testRIFFWave(QFile& rwFile);
    static WaveFormData* readRIFFWave(QFile& rwFile);
    static bool writeRIFFWave(QFile& rwFile, WaveFormData& wfData);

    // for Ogg Vorbis file
    static bool testOggVorbis(QFile& ovFile);
    static WaveFormData* readOggVorbis(QFile& ovFile);
    static bool writeOggVorbis(QFile& ovFile, WaveFormData& wfData);

    // for AAC file
    static bool testAAC(QFile& aacFile);
    static WaveFormData* readAAC(QFile& aacFile);
//    static bool writeAAC(QFile& aacFile, WaveFormData& wfData);

};

#endif // WAVEFORMRW_HPP
