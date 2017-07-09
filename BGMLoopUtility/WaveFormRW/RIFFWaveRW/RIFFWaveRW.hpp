#ifndef RIFFWAVERW_HPP
#define RIFFWAVERW_HPP

#include "WaveFormRW/WaveFormRW.hpp"

class RIFFWaveRW : public IWaveFormRW {
public:
    RIFFWaveRW();
    virtual ~RIFFWaveRW();

    bool test(QFile& file);
    WaveFormData* read(QFile& file);
};

#endif  // RIFFWAVERW_HPP
