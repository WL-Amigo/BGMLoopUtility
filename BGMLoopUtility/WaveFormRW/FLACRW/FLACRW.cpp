#include "FLACRW.hpp"
#include "decoder.h"

#include <QDebug>

FLACToWFDDecoder::FLACToWFDDecoder(WaveFormData *destWFD)
    : m_file(),
      m_totalSamples(0),
      m_sampleRate(0),
      m_channelNum(0),
      m_bps(0),
      m_wfdPtr(destWFD) {}

void FLACToWFDDecoder::setFile(QFile &file) {
    m_file.setFileName(file.fileName());
    if (!m_file.isOpen()) { m_file.open(QIODevice::ReadOnly); }
}

FLAC__StreamDecoderReadStatus FLACToWFDDecoder::read_callback(
    FLAC__byte buffer[], size_t *bytes) {
    /*if(*bytes > 0) {
    5     *bytes = fread(buffer, sizeof(FLAC__byte), *bytes, file);
    6     if(ferror(file))
    7       return FLAC__STREAM_DECODER_READ_STATUS_ABORT;
    8     else if(*bytes == 0)
    9       return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
   10     else
   11       return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
   12   }
   13   else
   14     return FLAC__STREAM_DECODER_READ_STATUS_ABORT;*/
    if (*bytes > 0) {
        *bytes = this->m_file.read(reinterpret_cast<char *>(buffer), *bytes);
        if (this->m_file.error() != QFileDevice::NoError) {
            return FLAC__STREAM_DECODER_READ_STATUS_ABORT;
        } else if (*bytes == 0) {
            return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
        } else {
            return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
        }
    } else {
        return FLAC__STREAM_DECODER_READ_STATUS_ABORT;
    }
}

FLAC__StreamDecoderWriteStatus FLACToWFDDecoder::write_callback(
    const FLAC__Frame *frame, const FLAC__int32 *const buffer[]) {
    const quint64 totalSize = static_cast<quint64>(
        this->m_totalSamples * this->m_channelNum * (this->m_bps / 8));

    if (this->m_totalSamples == 0) {
        qDebug().noquote()
            << "ERROR:FLACToWFDDecoder: this program only works for FLAC files "
               "that have a total_samples count in STREAMINFO";
        return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
    }
    if (this->m_channelNum > 3) {
        qDebug().noquote() << "ERROR:FLACToWFDDecoder: this program only works "
                              "for FLAC files that have channels less than 2";
        return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
    }
    if (this->m_wfdPtr == nullptr) {
        qDebug().noquote()
            << "ERROR:FLACToWFDDecoder: WaveFormData pointer isn't set";
        return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
    }

    for (unsigned i = 0; i < frame->header.blocksize; i++) {
        m_wfdPtr->lChannel.push_back(static_cast<qint16>(buffer[0][i]));
        m_wfdPtr->rChannel.push_back(static_cast<qint16>(buffer[1][i]));
    }

    return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void FLACToWFDDecoder::metadata_callback(
    const ::FLAC__StreamMetadata *metadata) {
    if (metadata->type == FLAC__METADATA_TYPE_STREAMINFO) {
        this->m_totalSamples = metadata->data.stream_info.total_samples;
        this->m_sampleRate = metadata->data.stream_info.sample_rate;
        this->m_channelNum = metadata->data.stream_info.channels;
        this->m_bps = metadata->data.stream_info.bits_per_sample;
    }
}

void FLACToWFDDecoder::error_callback(FLAC__StreamDecoderErrorStatus status) {
    qDebug().noquote() << "Got error callback:"
                       << FLAC__StreamDecoderErrorStatusString[status];
}

FLACRW::FLACRW() {}

FLACRW::~FLACRW() {}

bool FLACRW::test(QFile &file) {}

WaveFormData *FLACRW::read(QFile &file) {}
