#include "FLACRW.hpp"
#include "decoder.h"

FLACToWFDDecoder::FLACToWFDDecoder() {}

void FLACToWFDDecoder::setFile(QFile &file) {}

FLAC__StreamDecoderReadStatus FLACToWFDDecoder::read_callback(
    FLAC__byte buffer[], size_t *bytes) {}

FLAC__StreamDecoderWriteStatus FLACToWFDDecoder::write_callback(
    const FLAC__Frame *frame, const FLAC__int32 *const buffer[]) {}

void FLACToWFDDecoder::error_callback(FLAC__StreamDecoderErrorStatus status) {}

FLACRW::FLACRW() {}

FLACRW::~FLACRW() {}

bool FLACRW::test(QFile &file) {}

WaveFormData *FLACRW::read(QFile &file) {}
