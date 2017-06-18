#include "includes/WaveFormViewerBase.hpp"
#include <QPainter>
#include <QtMath>

static const qint16 MAX_INT16 = 32767;

WaveFormViewerBase::WaveFormViewerBase(QWidget* parent) : QWidget(parent) {}

void WaveFormViewerBase::drawWaveForm(WaveFormData& data, quint32 center,
                                      quint8 ratioExp, QColor color) {
    QPainter painter(this);
    auto width = this->width();
    auto height = this->height();

    auto harfWidth = width / 2;
    auto harfHeight = height / 2;
    auto quarterHeight = height / 4;

    // draw waveform
    for (int idx = (static_cast<int>(center) - harfWidth) < 0
                       ? harfWidth - static_cast<int>(center)
                       : 0;
         idx < width; idx++) {
        qint32 drawSamplePosition = static_cast<int>(center) - harfWidth + idx;
        auto samplePair =
            this->getDrawSampleHeight(data, drawSamplePosition, ratioExp);

        // draw L sample
        int sampleHeight = qRound(static_cast<qreal>(qAbs(samplePair.l)) /
                                  static_cast<qreal>(MAX_INT16) *
                                  static_cast<qreal>(quarterHeight));
        int y =
            (samplePair.l < 0) ? quarterHeight - sampleHeight : quarterHeight;
        painter.fillRect(idx, y, 1, sampleHeight, color);

        // draw R sample
        sampleHeight = qRound(static_cast<qreal>(qAbs(samplePair.l)) /
                              static_cast<qreal>(MAX_INT16) *
                              static_cast<qreal>(quarterHeight));
        y = (samplePair.r < 0) ? quarterHeight - sampleHeight : quarterHeight;
        y += harfHeight;
        painter.fillRect(idx, y, 1, sampleHeight, color);
    }
}

SamplePair WaveFormViewerBase::getDrawSampleHeight(WaveFormData& data,
                                                   quint32 drawSamplePos,
                                                   quint8 ratioExp) {
    quint32 ratio = 1;
    for (quint8 t = 1; t < ratioExp; t++) {
        ratio *= 2;
    }
    quint32 actualSamplePosition = drawSamplePos * ratio;

    // if ratio == 1, return raw value
    if (ratio == 1) {
        if (actualSamplePosition <= data.length()) {
            return {data.lChannel.at(actualSamplePosition),
                    data.rChannel.at(actualSamplePosition)};
        } else {  // if position is out of bound, return 0
            return {0, 0};
        }
    }

    // calcurate average from actualSamplePosition to
    // actualSamplePosition + ratio - 1
    qint32 sumL = 0;
    qint32 sumR = 0;
    for (quint32 idx = 0; idx < ratio; idx++) {
        if (idx + actualSamplePosition >= data.length()) break;
        sumL += data.lChannel.at(idx + actualSamplePosition);
        sumR += data.rChannel.at(idx + actualSamplePosition);
    }
    sumL /= ratio;
    sumR /= ratio;

    return {static_cast<qint16>(sumL), static_cast<qint16>(sumR)};
}
