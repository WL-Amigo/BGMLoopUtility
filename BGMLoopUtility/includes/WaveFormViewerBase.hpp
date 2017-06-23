#ifndef WAVEFORMVIEWERBASE_HPP
#define WAVEFORMVIEWERBASE_HPP

#include <QColor>
#include <QVector>
#include <QWidget>
#include "includes/WaveFormData.hpp"

struct SamplePair {
    qint16 lMax;
    qint16 rMax;
    qint16 lMin;
    qint16 rMin;
};

class WaveFormViewerBase : public QWidget {
    Q_OBJECT
public:
    explicit WaveFormViewerBase(QWidget* parent = nullptr);
    void setRatioExponential(quint8 ratioExp);
    void clearWaveFormCache();
    quint8 getRatioExponential();

protected:
    void drawWaveForm(WaveFormData& data, quint32 center, QColor color);
    SamplePair getDrawSampleHeight(WaveFormData& data, quint32 drawSamplePos);

private:
    quint8 m_ratioExp;
    QVector<SamplePair> m_spCache;

signals:

public slots:
};

#endif  // WAVEFORMVIEWERBASE_HPP
