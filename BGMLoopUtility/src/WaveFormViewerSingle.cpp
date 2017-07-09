#include "includes/WaveFormViewerSingle.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include "includes/Util.hpp"
#include "includes/WaveFormFileManager.hpp"

WaveFormViewerSingle::WaveFormViewerSingle(QWidget* parent)
    : WaveFormViewerBase(parent), centerSample(4096), m_isDragging(false) {
    this->waveFormData = nullptr;
    this->setRatioExponential(12);
}

void WaveFormViewerSingle::reloadWaveFormFile() {
    this->waveFormData = WaveFormFileManager::getInstance().getWaveFormData();
    this->update();
}

void WaveFormViewerSingle::paintEvent(QPaintEvent* event) {
    // prevent drawing before retrieving waveFormData
    if (this->waveFormData == nullptr) return;

    // draw waveform
    this->drawWaveForm(*(this->waveFormData),
                       this->centerSample >> this->getRatioExponential(),
                       Qt::black);
    // draw vertical center line
    QPainter painter(this);
    painter.fillRect(this->width() / 2, 0, 1, this->height(),
                     QColor(0, 0, 0, 128));
}

void WaveFormViewerSingle::setCenterSample(quint32 value) {
    this->centerSample = value;
    this->update();
    emit centerSampleChanged(value);
}

quint32 WaveFormViewerSingle::getCenterSample() { return this->centerSample; }

void WaveFormViewerSingle::mouseMoveEvent(QMouseEvent* event) {
    if (this->m_isDragging) {
        // move center sample by current ratio
        int dragLength = event->x() - this->m_dragStartX;
        this->setCenterSample(
            this->m_dragStartCenterSample -
            dragLength * Util::powerOfTwo(this->getRatioExponential()));
    }
}

void WaveFormViewerSingle::mousePressEvent(QMouseEvent* event) {
    // qDebug().noquote() << Q_FUNC_INFO << ": mouse pressed";
    if (event->button() == Qt::LeftButton) {
        this->m_isDragging = true;
        this->m_dragStartX = event->x();
        this->m_dragStartCenterSample = this->centerSample;
    }
}

void WaveFormViewerSingle::mouseReleaseEvent(QMouseEvent* event) {
    // qDebug().noquote() << Q_FUNC_INFO << ": mouse released";
    if (event->button() == Qt::LeftButton) this->m_isDragging = false;
}
