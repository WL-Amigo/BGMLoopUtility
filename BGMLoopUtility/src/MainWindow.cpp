#include "includes/MainWindow.hpp"
#include "Core/WaveFormFileManager.hpp"
#include "includes/AcceptDropLabel.hpp"
#include "ui_MainWindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      lpdGUI(new LoopPointDetectorGUI(nullptr)) {
    ui->setupUi(this);

    // connect basic behavior
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    // connect application behavior
    connect(ui->fileInfoLabel, &AcceptDropLabel::fileDropped, this,
            &MainWindow::onFileLoad);
    connect(ui->browseButton, &QPushButton::clicked, this,
            &MainWindow::onBrowse);
    connect(ui->buttonSALD, &QToolButton::clicked, lpdGUI,
            &LoopPointDetectorGUI::show);

    // disable tool buttons
    ui->buttonSALD->setEnabled(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onBrowse() {
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setNameFilter(tr("wave-form file (*.wav)"));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (fileDialog.exec()) {
        onFileLoad(fileDialog.selectedFiles().at(0));
    }
}

void MainWindow::onDragAndDrop() {}

void MainWindow::onFileLoad(QString filename) {
    if (WaveFormFileManager::getInstance().open(filename)) {
        ui->fileInfoLabel->setText(filename);
        enableToolButtons(WaveFormFileManager::getInstance().getFileType());
    }
}

static bool AVAILABLE_TOOL_SET[][1] = {
    // 0 : Semi-auto loop point detector
    {true},   // RIFF Wave
    {false},  // Ogg Vorbis
    {false}   // AAC
};

void MainWindow::enableToolButtons(WaveFormFileType wfFileType) {
    if (wfFileType == WaveFormFileType::UNKNOWN)
        return;
    else {
        ui->buttonSALD->setEnabled(
            AVAILABLE_TOOL_SET[static_cast<int>(wfFileType)][0]);
    }
}
