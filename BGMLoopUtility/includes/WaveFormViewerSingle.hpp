#ifndef WAVEFORMVIEWERSINGLE_HPP
#define WAVEFORMVIEWERSINGLE_HPP

#include "includes/WaveFormViewerBase.hpp"

class WaveFormViewerSingle : public WaveFormViewerBase {
    Q_OBJECT

public:
    explicit WaveFormViewerSingle(QWidget* parent = nullptr);
    void reloadWaveFormFile();

protected:
    void paintEvent(QPaintEvent* event) override;

    // getter/setter
public:
    void setCenterSample(quint32 value);
    quint32 getCenterSample();
    void setRatioExp(quint8 value);
    quint8 getRatioExp();

private:
    WaveFormData* waveFormData;
    quint32 centerSample;
    quint8 ratioExp;
};

#endif  // WAVEFORMVIEWERSINGLE_HPP
