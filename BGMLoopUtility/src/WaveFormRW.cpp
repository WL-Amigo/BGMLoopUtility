#include "includes/WaveFormRW.hpp"
#include "includes/BytesToIntUtility.hpp"
#include <QAudioDecoder>
#include <QByteArray>
#include <QDebug>
#include <QThread>

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

bool checkRIFFWaveFormat(const QByteArray& formatChunk){
    // formatChunk should be content of format chunk (without "fmt " and size)
    return formatChunk[0] == 0x01 && formatChunk[1] == 0x00 // it should be Linear PCM Format
            && formatChunk[2] == 0x02 && formatChunk[3] == 0x00 // channel # should be 2
            && (BytesToIntUtility::toUInt32(formatChunk.mid(4,4)) * 4 == BytesToIntUtility::toUInt32(formatChunk.mid(8,4))) // validity check
            && formatChunk[12] == 0x04 && formatChunk[13] == 0x00 // block size should be 2 x 2
            && formatChunk[14] == 0x10 && formatChunk[15] == 0x00; // bit depth should be 16
}

bool WaveFormRW::testRIFFWave(QFile& rwFile) {
    rwFile.seek(0);
    QByteArray header = rwFile.read(12);
    if(!(header.mid(0, 4) == "RIFF") || !(header.mid(8, 4) == "WAVE")) return false;
    return true;
}

WaveFormData* WaveFormRW::readRIFFWave(QFile& rwFile) {
    // read all as byte array
    QByteArray data = rwFile.readAll();
    if(data.isNull()) return false;

    // check applicability of inputed file
    int fmtIndex = data.indexOf("fmt ");
    if(fmtIndex < 0) return false;
    quint32 fmtSize = BytesToIntUtility::toUInt32(data.mid(fmtIndex + 4,4));
    if(!checkRIFFWaveFormat(data.mid(fmtIndex + 8,fmtSize))) return false;
    qDebug() << "check applicability: pass";

    // get sample rate
//    this->sampleRate = this->getSampleRate(data.mid(fmtIndex + 8, fmtSize));
//    qDebug() << "sample rate:" << this->sampleRate;

    // get wave form data
    int dataIndex = data.indexOf("data");
    if(dataIndex < 0) return false;
    quint32 dataSize = BytesToIntUtility::toUInt32(data.mid(dataIndex + 4,4));
    if(dataSize < 0) return false;
    WaveFormData* wfd = new WaveFormData();
    wfd->push(data.mid(dataIndex + 8, dataSize), 2);

    return wfd;
}

bool WaveFormRW::writeRIFFWave(QFile& rwFile, WaveFormData& wfData) { return false; }

// for Ogg Vorbis file
bool WaveFormRW::testOggVorbis(QFile& ovFile) { return false; }

WaveFormData* WaveFormRW::readOggVorbis(QFile& ovFile) { return nullptr; }

bool WaveFormRW::writeOggVorbis(QFile& ovFile, WaveFormData& wfData) { return false; }

// for AAC file
bool WaveFormRW::testAAC(QFile& aacFile) { return false; }

WaveFormData* WaveFormRW::readAAC(QFile& aacFile) { return nullptr; }

//     bool WaveFormRW::writeAAC(QFile& aacFile, WaveFormData& wfData);
