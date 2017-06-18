#include "includes/WaveFormData.hpp"
#include "includes/BytesToIntUtility.hpp"

WaveFormData::WaveFormData() {}

bool WaveFormData::push(QAudioBuffer& buf) {
    if (buf.format().channelCount() != 2) return false;   // stereo
    if (buf.format().bytesPerFrame() != 4) return false;  // 16bit

    // read into vector
    const qint16* bufRaw = buf.constData<qint16>();
    for (quint32 sidx = 0; sidx < buf.frameCount(); sidx += 2) {
        lChannel.push_back(*(bufRaw + sidx));
        rChannel.push_back(*(bufRaw + sidx + 1));
    }

    return true;
}

bool WaveFormData::push(const QByteArray& buf, qint8 byteDepth) {
    if (byteDepth == 2) {
        for (quint32 sidx = 0; sidx < buf.size(); sidx += 4) {
            lChannel.push_back(BytesToIntUtility::toInt16(buf.mid(sidx, 2)));
            rChannel.push_back(
                BytesToIntUtility::toInt16(buf.mid(sidx + 2, 2)));
        }
    } else {  // only support 16bit pcm in current
        return false;
    }

    return false;
}

quint32 WaveFormData::length() {
    Q_ASSERT(this->lChannel.length() == this->rChannel.length());
    return static_cast<quint32>(this->lChannel.length());
}
