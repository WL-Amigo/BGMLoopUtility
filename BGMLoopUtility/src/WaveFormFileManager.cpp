#include "includes/WaveFormFileManager.hpp"

WaveFormFileManager::WaveFormFileManager() :
    currentFile(),
    currentFileType(WaveFormFileType::UNKNOWN),
    wfData(nullptr),
    loopInfoFileName()
{

}

QString removeExtention(QString fileName){
    return fileName.mid(0, fileName.lastIndexOf(".") + 1);
}

bool WaveFormFileManager::open(QString filePath){
    // close before load new file
    close();

    // try to open file by filePath
    this->currentFile.setFileName(filePath);
    if(!currentFile.exists()){
        // TODO: report error
        this->currentFile.setFileName("");
        return false;
    }
    if(!currentFile.open(QFileDevice::ReadOnly)){
        // TODO: report error
        this->currentFile.setFileName("");
        return false;
    }

    // try to decode file and get wave-form data
    this->wfData = WaveFormRW::read(this->currentFile);
    if(this->wfData == nullptr){
        // TODO: report error
        this->currentFile.close();
        this->currentFile.setFileName("");
        return false;
    }

    // get file type
    this->currentFileType = WaveFormRW::test(this->currentFile);

    // set default loop info file name
    this->loopInfoFileName = removeExtention(filePath) + "_loopinfo.json";

    return true;
}

bool WaveFormFileManager::close(){
    if(isOpened()){
        // destroy wave-form data
        delete this->wfData;

        // close file
        this->currentFile.close();
        this->currentFile.setFileName("");

        // reset file type
        this->currentFileType = WaveFormFileType::UNKNOWN;
    }

    return true;
}

bool WaveFormFileManager::isOpened(){
    return this->wfData != nullptr && this->currentFile.isOpen();
}

WaveFormFileType WaveFormFileManager::getFileType(){
    return this->currentFileType;
}

WaveFormData* WaveFormFileManager::getWaveFormData(){
    return this->wfData;
}

QString WaveFormFileManager::getLoopInfoFileName(){ return this->loopInfoFileName; }
