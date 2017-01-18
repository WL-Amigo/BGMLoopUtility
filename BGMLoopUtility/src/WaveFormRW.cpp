#include "includes/WaveFormRW.hpp"

WaveFormRW::WaveFormRW() {}

WaveFormFileType WaveFormRW::test(QFile& wfFile) {
    if (WaveFormRW::testRIFFWave(wfFile))
        return WaveFormFileType::RIFFWAVE;
    else if (WaveFormRW::testOggVorbis(wfFile))
        return WaveFormFileType::OGGVORBIS;
    else if (WaveFormRW::testAAC(wfFile))
        return WaveFormFileType::AAC;
    else
        return WaveFormFileType::UNKNOWN;
}

WaveFormData* WaveFormRW::read(QFile& wfFile) {
    WaveFormFileType type = WaveFormRW::test(wfFile);

    if (type == WaveFormFileType::RIFFWAVE)
        return WaveFormRW::readRIFFWave(wfFile);
    else if (type == WaveFormFileType::OGGVORBIS)
        return WaveFormRW::readOggVorbis(wfFile);
    else if (type == WaveFormFileType::AAC)
        return WaveFormRW::readAAC(wfFile);
    else
        return nullptr;
}

bool WaveFormRW::write(QFile& destFile, WaveFormFileType fileType,
                       WaveFormData& wfData) {
    if (fileType == WaveFormFileType::RIFFWAVE)
        return WaveFormRW::writeRIFFWave(destFile, wfData);
    else if (fileType == WaveFormFileType::OGGVORBIS)
        return WaveFormRW::writeOggVorbis(destFile, wfData);
    else if (fileType == WaveFormFileType::AAC)
        return false;
    else
        return false;
}

// for RIFF Wave file
bool WaveFormRW::testRIFFWave(QFile& rwFile) { return false; }

WaveFormData* WaveFormRW::readRIFFWave(QFile& rwFile) { return nullptr; }

bool WaveFormRW::writeRIFFWave(QFile& rwFile, WaveFormData& wfData) { return false; }

// for Ogg Vorbis file
bool WaveFormRW::testOggVorbis(QFile& ovFile) { return false; }

WaveFormData* WaveFormRW::readOggVorbis(QFile& ovFile) { return nullptr; }

bool WaveFormRW::writeOggVorbis(QFile& ovFile, WaveFormData& wfData) { return false; }

// for AAC file
bool WaveFormRW::testAAC(QFile& aacFile) { return false; }

WaveFormData* WaveFormRW::readAAC(QFile& aacFile) { return nullptr; }

//     bool WaveFormRW::writeAAC(QFile& aacFile, WaveFormData& wfData);
