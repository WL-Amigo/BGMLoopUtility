#include "includes/AcceptDropLabel.hpp"
#include <QDebug>
#include <QMimeData>
#include <QUrl>

AcceptDropLabel::AcceptDropLabel(QWidget *parent) { setAcceptDrops(true); }

void AcceptDropLabel::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasText()) {
        if (getFullPathFromEvent(event).size() > 0) {
            event->acceptProposedAction();
        }
    }
}

void AcceptDropLabel::dropEvent(QDropEvent *event) {
    QString fullPath = getFullPathFromEvent(event);
    qDebug() << fullPath;
    emit fileDropped(fullPath);
}

static bool checkExtention(QString &filename, QString extention) {
    // extention: file extention WITHOUT dot(.)
    extention = QString(".") + extention;
    return filename.indexOf(extention, filename.length() - extention.length(),
                            Qt::CaseInsensitive)
           == filename.length() - extention.length();
}

QString AcceptDropLabel::getFullPathFromEvent(QDropEvent *event) {
    QString mimeText = event->mimeData()->text();
    mimeText.replace('\n', "");
    mimeText.replace('\r', "");
    mimeText.replace("file://", "");
    if (checkExtention(mimeText, "wav")) {  // accept only .wav file
        return QUrl::fromPercentEncoding(mimeText.toUtf8());
    } else if (checkExtention(mimeText, "flac")) {
        return QUrl::fromPercentEncoding(mimeText.toUtf8());
    }

    return "";
}
