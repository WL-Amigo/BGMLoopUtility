#ifndef FLACRW_HPP
#define FLACRW_HPP

#include "WaveFormRW/WaveFormRW.hpp"
#include "decoder.h"

class FLACToWFDDecoder : public FLAC::Decoder::Stream {
public:
    FLACToWFDDecoder(WaveFormData* destWFD);
    void setFile(QFile& file);

protected:
    virtual FLAC__StreamDecoderWriteStatus write_callback(
        const FLAC__Frame* frame, const FLAC__int32* const buffer[]);
    virtual FLAC__StreamDecoderReadStatus read_callback(FLAC__byte buffer[],
                                                        size_t* bytes);
    virtual void metadata_callback(const ::FLAC__StreamMetadata* metadata);
    virtual void error_callback(FLAC__StreamDecoderErrorStatus status);

private:
    QFile m_file;
    quint64 m_totalSamples;
    quint32 m_sampleRate;
    quint32 m_channelNum;
    quint32 m_bps;
    WaveFormData* m_wfdPtr;
};

class FLACRW : public IWaveFormRW {
public:
    FLACRW();
    virtual ~FLACRW();

    bool test(QFile& file);
    WaveFormData* read(QFile& file);
};

#endif  // FLACRW_HPP
