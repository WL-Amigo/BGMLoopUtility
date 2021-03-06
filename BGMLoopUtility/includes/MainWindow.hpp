#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "includes/LoopPointDetectorGUI.hpp"
#include "includes/WaveFormFileType.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void enableToolButtons(WaveFormFileType wfFileType);

private slots:
    void onBrowse();
    void onDragAndDrop();
    void onFileLoad(QString filename);

private:
    Ui::MainWindow *ui;
    LoopPointDetectorGUI *lpdGUI;
};

#endif // MAINWINDOW_HPP
