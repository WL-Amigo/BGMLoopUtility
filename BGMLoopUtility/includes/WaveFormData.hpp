#ifndef WAVEFORMDATA_HPP
#define WAVEFORMDATA_HPP

#include <QVector>
#include <QAudioBuffer>
#include <QByteArray>

class WaveFormData
{
public:
    WaveFormData();
    bool push(const QByteArray& buf, qint8 byteDepth);
    bool push(QAudioBuffer& buf);
    quint32 length();

public:
    QVector<qint16> lChannel;
    QVector<qint16> rChannel;
};

#endif // WAVEFORMDATA_HPP
