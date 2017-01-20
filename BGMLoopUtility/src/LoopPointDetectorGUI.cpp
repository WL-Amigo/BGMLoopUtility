#include "includes/LoopPointDetectorGUI.hpp"
#include "ui_LoopPointDetectorGUI.h"

#include <QPushButton>
#include <QSpinBox>
#include <QShowEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

#include "includes/WaveFormFileManager.hpp"

LoopPointDetectorGUI::LoopPointDetectorGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoopPointDetectorGUI),
    lpd()
{
    ui->setupUi(this);

    // connect behavior
    connect(ui->quitButton, &QPushButton::clicked, this, &LoopPointDetectorGUI::close);
    connect(ui->detectButton, &QPushButton::clicked, this, &LoopPointDetectorGUI::startDetection);
}

LoopPointDetectorGUI::~LoopPointDetectorGUI()
{
    delete ui;
}

void LoopPointDetectorGUI::showEvent(QShowEvent *event){
    // set total sample label
    quint32 sampleLength = WaveFormFileManager::getInstance().getWaveFormData()->lChannel.size();
    QString sampleLabelContent = tr("current file's total samples:") + " " + QString::asprintf("%ld", sampleLength);
    ui->totalSampleLabel->setText(sampleLabelContent);
}

void LoopPointDetectorGUI::startDetection(){
    // get assumed LOOPEND from spinbox
    quint32 assumedLoopEnd = ui->loopEndSample->text().toInt();

    // spawn detection method
    bool success = lpd.detectLoopStart(assumedLoopEnd);

    // show message box
    if(success){
        QMessageBox msgBox;
        msgBox.setText(tr("loop point have been found!"));
        msgBox.setInformativeText(QString("LOOPSTART: ") + QString::asprintf("%ld", lpd.getLoopStart())
                                  + "\nLOOPLENGTH: " + QString::asprintf("%ld", lpd.getLoopLength())
                                  + "\n" + tr("Do you want to save this?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setDefaultButton(QMessageBox::Save);
        int msgResult = msgBox.exec();
        if(msgResult == QMessageBox::Save){
            saveLoopInfo();
        }
    } else {
        QMessageBox msgBox;
        msgBox.setText(tr("loop point was not found..."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void LoopPointDetectorGUI::saveLoopInfo(){
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setNameFilter(tr("json file (*.json)"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.selectFile(WaveFormFileManager::getInstance().getLoopInfoFileName());
    if(fileDialog.exec()){
        QString fileName = fileDialog.selectedFiles().at(0);
        QFile file(fileName);
        QJsonDocument json;
        QJsonObject obj;

        // write loop information to JSON Object
        obj.insert("LOOPSTART", static_cast<qint64>(lpd.getLoopStart()));
        obj.insert("LOOPLENGTH", static_cast<qint64>(lpd.getLoopLength()));
        json.setObject(obj);

        // open file in write mode
        if(!file.open(QIODevice::WriteOnly)) return;

        // write JSON Document to file
        file.write(json.toJson());
    }
}
