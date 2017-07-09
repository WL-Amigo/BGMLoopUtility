#include "RIFFWaveRW.hpp"
#include "Core/BytesToIntUtility.hpp"
#include "WaveFormRW/WaveFormRW.hpp"

RIFFWaveRW::RIFFWaveRW() {}

RIFFWaveRW::~RIFFWaveRW() {}

static bool checkRIFFWaveFormat(const QByteArray& formatChunk) {
    // formatChunk should be content of format chunk (without "fmt " and size)
    return formatChunk[0] == 0x01 &&
           formatChunk[1] == 0x00  // it should be Linear PCM Format
           && formatChunk[2] == 0x02 &&
           formatChunk[3] == 0x00  // channel # should be 2
           && (BytesToIntUtility::toUInt32(formatChunk.mid(4, 4)) * 4 ==
               BytesToIntUtility::toUInt32(
                   formatChunk.mid(8, 4)))  // validity check
           && formatChunk[12] == 0x04 &&
           formatChunk[13] == 0x00  // block size should be 2 x 2
           && formatChunk[14] == 0x10 &&
           formatChunk[15] == 0x00;  // bit depth should be 16
}

bool RIFFWaveRW::test(QFile& file) {
    file.seek(0);
    QByteArray header = file.read(12);
    if (!(header.mid(0, 4) == "RIFF") || !(header.mid(8, 4) == "WAVE"))
        return false;
    return true;
}

WaveFormData* RIFFWaveRW::read(QFile& file) {
    // read all as byte array
    QByteArray data = file.readAll();
    if (data.isNull()) return nullptr;

    // check applicability of inputed file
    int fmtIndex = data.indexOf("fmt ");
    if (fmtIndex < 0) return nullptr;
    quint32 fmtSize = BytesToIntUtility::toUInt32(data.mid(fmtIndex + 4, 4));
    if (!checkRIFFWaveFormat(data.mid(fmtIndex + 8, fmtSize))) return nullptr;
    qDebug() << "check applicability: pass";

    // get sample rate
    //    this->sampleRate = this->getSampleRate(data.mid(fmtIndex + 8,
    //    fmtSize));
    //    qDebug() << "sample rate:" << this->sampleRate;

    // get wave form data
    int dataIndex = data.indexOf("data");
    if (dataIndex < 0) return nullptr;
    quint32 dataSize = BytesToIntUtility::toUInt32(data.mid(dataIndex + 4, 4));
    if (dataSize < 0) return nullptr;
    WaveFormData* wfd = new WaveFormData();
    wfd->push(data.mid(dataIndex + 8, dataSize), 2);

    return wfd;
}
