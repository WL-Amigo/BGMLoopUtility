#include "includes/LoopPointDetector.hpp"

#include "includes/WaveFormFileManager.hpp"
#include "includes/WaveFormData.hpp"

LoopPointDetector::LoopPointDetector():
    loopStart(0),
    loopLength(0),
    sameRange(4410)
{

}

bool LoopPointDetector::detectLoopStart(quint32 assumedLoopEnd){
    // get wave form data from manager
    WaveFormData* wfd = WaveFormFileManager::getInstance().getWaveFormData();

    // get samples around point
    quint32 harfSR = this->sameRange / 2;
    QVector<qint16> samplesToFindL = wfd->lChannel.mid(assumedLoopEnd - harfSR, this->sameRange);
    QVector<qint16> samplesToFindR = wfd->rChannel.mid(assumedLoopEnd - harfSR, this->sameRange);

    // try to found almost same point
    quint32 index = harfSR;
    quint32 endOfSearch = assumedLoopEnd - this->sameRange;
    if(endOfSearch > assumedLoopEnd) return false;
    for(;index < endOfSearch; index++){
        quint32 rangeIdx = 0;
        for(;rangeIdx < this->sameRange; rangeIdx++){
            bool cL = checkCongruencySample(samplesToFindL[rangeIdx],
                                      wfd->lChannel[index - harfSR + rangeIdx]);
            bool cR = checkCongruencySample(samplesToFindR[rangeIdx],
                                      wfd->rChannel[index - harfSR + rangeIdx]);
            if(!(cL && cR)) {
                break;
            }
        }
        if(rangeIdx == this->sameRange){ // find almost same point
            this->loopStart = index;
            this->loopLength = assumedLoopEnd - index;
            return true;
        }
    }

    // if the program reached this line, that means almost same point is not found
    return false;
}

bool LoopPointDetector::detectLoopStartSemiauto(quint32 assumedLoopEnd, quint32 skipSample, quint16 trialNumber){
    for(quint16 num = 0; num < trialNumber; num++){
        if(detectLoopStart(assumedLoopEnd)) return true; // found LOOPSTART
        // if detection failed, move assumedLoopEnd backward by skipSample and retry to detect
        assumedLoopEnd -= skipSample;
    }

    // if the program reached this line, that means LOOPSTART is not found
    return false;
}

static qint16 ACCEPT_RANGE = 400;

bool LoopPointDetector::checkCongruencySample(qint16 lhs, qint16 rhs){
    lhs /= 16;
    rhs /= 16;
    return (rhs > lhs - ACCEPT_RANGE) && (rhs < lhs + ACCEPT_RANGE);
}


void LoopPointDetector::setSameRange(quint32 newSameRange){
    this->sameRange = newSameRange;
}
