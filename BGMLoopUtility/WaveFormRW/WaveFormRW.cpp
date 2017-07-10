#include "WaveFormRW.hpp"
#include "FLACRW/FLACRW.hpp"
#include "RIFFWaveRW/RIFFWaveRW.hpp"

// dummy methods for abstract class

IWaveFormRW::IWaveFormRW() {}
IWaveFormRW::~IWaveFormRW() {}

// map definition

QMap<WaveFormFileType, IWaveFormRW*> WaveFormRW::s_fileTypeToRWer
    = {{WaveFormFileType::RIFFWAVE, new RIFFWaveRW()},
       {WaveFormFileType::FLAC, new FLACRW()}};

WaveFormFileType WaveFormRW::test(QFile& wfFile) {
    auto it = s_fileTypeToRWer.constBegin();
    while (it != s_fileTypeToRWer.constEnd()) {
        if (it.value()->test(wfFile)) return it.key();
        it++;
    }
    return WaveFormFileType::UNKNOWN;
}

WaveFormData* WaveFormRW::read(QFile& wfFile) {
    WaveFormFileType type = WaveFormRW::test(wfFile);
    if (type != WaveFormFileType::UNKNOWN) {
        return s_fileTypeToRWer[type]->read(wfFile);
    } else
        return nullptr;
}
