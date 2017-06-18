#include "includes/WaveFormViewerSingle.hpp"
#include <QPainter>
#include "includes/WaveFormFileManager.hpp"

WaveFormViewerSingle::WaveFormViewerSingle(QWidget* parent)
    : WaveFormViewerBase(parent), centerSample(4096), ratioExp(1) {
    this->waveFormData = nullptr;
}

void WaveFormViewerSingle::reloadWaveFormFile() {
    this->waveFormData = WaveFormFileManager::getInstance().getWaveFormData();
    this->update();
}

void WaveFormViewerSingle::paintEvent(QPaintEvent* event) {
    // prevent drawing before retrieving waveFormData
    if (this->waveFormData == nullptr) return;

    // draw waveform
    this->drawWaveForm(*(this->waveFormData), this->centerSample >> ratioExp,
                       ratioExp, Qt::black);
    // draw vertical center line
    QPainter painter(this);
    painter.fillRect(this->width() / 2, 0, 1, this->height(),
                     QColor(0, 0, 0, 128));
}
