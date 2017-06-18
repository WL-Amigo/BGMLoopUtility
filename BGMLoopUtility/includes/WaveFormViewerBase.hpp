#ifndef WAVEFORMVIEWERBASE_HPP
#define WAVEFORMVIEWERBASE_HPP

#include <QColor>
#include <QWidget>
#include "includes/WaveFormData.hpp"

struct SamplePair {
    qint16 l;
    qint16 r;
};

class WaveFormViewerBase : public QWidget {
    Q_OBJECT
public:
    explicit WaveFormViewerBase(QWidget* parent = nullptr);

protected:
    void drawWaveForm(WaveFormData& data, quint32 center, quint8 ratioExp,
                      QColor color);
    SamplePair getDrawSampleHeight(WaveFormData& data, quint32 drawSamplePos,
                                   quint8 ratioExp);

private:
signals:

public slots:
};

#endif  // WAVEFORMVIEWERBASE_HPP
