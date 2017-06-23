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
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    // getter/setter
public:
    void setCenterSample(quint32 value);
    quint32 getCenterSample();

private:
    WaveFormData* waveFormData;
    quint32 centerSample;
    bool m_isDragging;
    int m_dragStartX;
    quint32 m_dragStartCenterSample;

    // signals
signals:
    void centerSampleChanged(quint32 sample);
};

#endif  // WAVEFORMVIEWERSINGLE_HPP
