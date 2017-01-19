#include "includes/MainWindow.hpp"
#include "ui_MainWindow.h"
#include "includes/WaveFormFileManager.hpp"
#include "includes/AcceptDropLabel.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect basic behavior
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    // connect application behavior
    connect(ui->fileInfoLabel, &AcceptDropLabel::fileDropped, this, &MainWindow::onFileLoad);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBrowse(){

}

void MainWindow::onDragAndDrop(){

}

void MainWindow::onFileLoad(QString filename){
    if(WaveFormFileManager::getInstance().open(filename)){
        ui->fileInfoLabel->setText(filename);
    }
}
