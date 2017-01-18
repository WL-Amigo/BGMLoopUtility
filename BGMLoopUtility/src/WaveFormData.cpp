#include "includes/WaveFormData.hpp"

WaveFormData::WaveFormData()
{

}

bool WaveFormData::push(QAudioBuffer& buf){
    if(buf.format().channelCount() != 2) return false; // stereo
    if(buf.format().bytesPerFrame() != 4) return false; // 16bit

    // read into vector
    const qint16* bufRaw = buf.constData<qint16>();
    for(quint32 sidx = 0; sidx < buf.frameCount(); sidx += 2){
        lChannel.push_back(*(bufRaw + sidx));
        rChannel.push_back(*(bufRaw + sidx + 1));
    }

    return true;
}
