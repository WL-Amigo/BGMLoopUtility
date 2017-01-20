#ifndef LOOPPOINTDETECTOR_HPP
#define LOOPPOINTDETECTOR_HPP

#include <QtCore>

class LoopPointDetector
{
public:
    LoopPointDetector();
    bool detectLoopStart(quint32 assumedLoopEnd);
    bool detectLoopStartSemiauto(quint32 assumedLoopEnd, quint32 skipSample = 1000, quint16 trialNumber = 100);
    void setSameRange(quint32 newSameRange);

private:
    bool checkCongruencySample(qint16 lhs, qint16 rhs);

private:
    quint32 loopStart;
    quint32 loopLength;
    quint32 sameRange;

};

#endif // LOOPPOINTDETECTOR_HPP
