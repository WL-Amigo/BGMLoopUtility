#ifndef WAVEFORMDATA_HPP
#define WAVEFORMDATA_HPP

#include <QVector>
#include <QAudioBuffer>

class WaveFormData
{
public:
    WaveFormData();
    bool push(QAudioBuffer& buf);

public:
    QVector<qint16> lChannel;
    QVector<qint16> rChannel;
};

#endif // WAVEFORMDATA_HPP
