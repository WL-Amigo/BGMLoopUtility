#ifndef FLACRW_HPP
#define FLACRW_HPP

#include "WaveFormRW/WaveFormRW.hpp"
#include "decoder.h"

class FLACToWFDDecoder : public FLAC::Decoder::Stream {
public:
    FLACToWFDDecoder();
    void setFile(QFile& file);

protected:
    virtual FLAC__StreamDecoderWriteStatus write_callback(
        const FLAC__Frame* frame, const FLAC__int32* const buffer[]);
    virtual FLAC__StreamDecoderReadStatus read_callback(FLAC__byte buffer[],
                                                        size_t* bytes);
    virtual void error_callback(FLAC__StreamDecoderErrorStatus status);
};

class FLACRW : public IWaveFormRW {
public:
    FLACRW();
    virtual ~FLACRW();

    bool test(QFile& file);
    WaveFormData* read(QFile& file);
};

#endif  // FLACRW_HPP
