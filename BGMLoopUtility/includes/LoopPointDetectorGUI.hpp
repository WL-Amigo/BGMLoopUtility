#ifndef LOOPPOINTDETECTORGUI_HPP
#define LOOPPOINTDETECTORGUI_HPP

#include <QWidget>

#include "includes/LoopPointDetector.hpp"

namespace Ui {
class LoopPointDetectorGUI;
}

class LoopPointDetectorGUI : public QWidget
{
    Q_OBJECT

public:
    explicit LoopPointDetectorGUI(QWidget *parent = 0);
    ~LoopPointDetectorGUI();

private:
    void showEvent(QShowEvent *event);

private slots:
    void startDetection();
    void saveLoopInfo();

private:
    Ui::LoopPointDetectorGUI *ui;
    LoopPointDetector lpd;
};

#endif // LOOPPOINTDETECTORGUI_HPP
