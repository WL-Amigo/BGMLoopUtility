#include "includes/WaveFormViewerBase.hpp"
#include <QPainter>
#include <QtMath>

static const qint32 MAX_UINT16 = 65535;
static const qint32 MAX_INT16 = 32767;

WaveFormViewerBase::WaveFormViewerBase(QWidget* parent)
    : QWidget(parent), m_ratioExp(0), m_spCache() {}

void WaveFormViewerBase::setRatioExponential(quint8 ratioExp) {
    this->m_ratioExp = ratioExp;
    this->clearWaveFormCache();
}

void WaveFormViewerBase::clearWaveFormCache() { this->m_spCache.clear(); }

quint8 WaveFormViewerBase::getRatioExponential() { return this->m_ratioExp; }

void WaveFormViewerBase::drawWaveForm(WaveFormData& data, quint32 center,
                                      QColor color) {
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
        auto samplePair = this->getDrawSampleHeight(data, drawSamplePosition);

        // draw L sample
        int yMax = qRound(static_cast<qreal>(samplePair.lMax) /
                          static_cast<qreal>(MAX_UINT16) *
                          static_cast<qreal>(quarterHeight));
        int yMin = qRound(static_cast<qreal>(samplePair.lMin) /
                          static_cast<qreal>(MAX_UINT16) *
                          static_cast<qreal>(quarterHeight));
        int sampleHeight = yMax - yMin;
        int y = quarterHeight - yMax;
        painter.fillRect(idx, y, 1, sampleHeight, color);

        // draw R sample
        yMax = qRound(static_cast<qreal>(samplePair.rMax) /
                      static_cast<qreal>(MAX_UINT16) *
                      static_cast<qreal>(quarterHeight));
        yMin = qRound(static_cast<qreal>(samplePair.rMin) /
                      static_cast<qreal>(MAX_UINT16) *
                      static_cast<qreal>(quarterHeight));
        sampleHeight = yMax - yMin;
        y = quarterHeight - yMax;
        y += harfHeight;
        painter.fillRect(idx, y, 1, sampleHeight, color);
    }
}

SamplePair WaveFormViewerBase::getDrawSampleHeight(WaveFormData& data,
                                                   quint32 drawSamplePos) {
    quint32 ratio = 1;
    for (quint8 t = 0; t < this->m_ratioExp; t++) {
        ratio *= 2;
    }
    quint32 actualSamplePosition = drawSamplePos * ratio;

    // if ratio == 0, return raw value
    if (ratio == 0) {
        auto lValue = data.lChannel.at(actualSamplePosition);
        auto rValue = data.rChannel.at(actualSamplePosition);
        if (actualSamplePosition <= data.length()) {
            return {lValue >= 0 ? lValue : static_cast<qint16>(0),
                    rValue >= 0 ? rValue : static_cast<qint16>(0),
                    lValue < 0 ? lValue : static_cast<qint16>(0),
                    rValue < 0 ? rValue : static_cast<qint16>(0)};
        } else {  // if position is out of bound, return 0
            return {0, 0, 0, 0};
        }
    }

    // if cache is available, return value from cache
    if (this->m_spCache.length() > drawSamplePos &&
        this->m_spCache.at(drawSamplePos).lMax >= 0)
        return this->m_spCache.at(drawSamplePos);

    // calcurate max/min from actualSamplePosition to
    // actualSamplePosition + ratio - 1
    SamplePair result = {0, 0, 0, 0};
    for (quint32 idx = 0; idx < ratio; idx++) {
        if (idx + actualSamplePosition >= data.length()) break;
        auto lValue = data.lChannel.at(idx + actualSamplePosition);
        auto rValue = data.rChannel.at(idx + actualSamplePosition);
        if (result.lMax < lValue) result.lMax = lValue;
        if (result.rMax < rValue) result.rMax = rValue;
        if (result.lMin > lValue) result.lMin = lValue;
        if (result.rMin > rValue) result.rMin = rValue;
    }

    // save result to cache
    while (this->m_spCache.length() < drawSamplePos) {
        this->m_spCache.push_back({-1, -1, 1, 1});
    }
    if (this->m_spCache.length() == drawSamplePos) {
        this->m_spCache.push_back(result);
    } else {  // length > drawSamplePos
        this->m_spCache[drawSamplePos] = result;
    }

    return result;
}
