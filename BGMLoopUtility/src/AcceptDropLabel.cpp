#include "includes/AcceptDropLabel.hpp"
#include <QMimeData>

AcceptDropLabel::AcceptDropLabel(QWidget *parent)
{
    setAcceptDrops(true);
}

void AcceptDropLabel::dragEnterEvent(QDragEnterEvent *event){
    if(event->mimeData()->hasText()){
        if(getFullPathFromEvent(event).size() > 0){
            event->acceptProposedAction();
        }
    }
}

void AcceptDropLabel::dropEvent(QDropEvent *event){
    QString fullPath = getFullPathFromEvent(event);
    emit fileDropped(fullPath);
}

QString AcceptDropLabel::getFullPathFromEvent(QDropEvent *event){
    QString mimeText = event->mimeData()->text();
    mimeText.replace('\n', "");
    mimeText.replace('\r', "");
    mimeText.replace("file://", "");
    if(mimeText.indexOf(".wav", 0, Qt::CaseInsensitive) >= mimeText.size() - 4){ // accept only .wav file
        return mimeText;
    }

    return "";
}
