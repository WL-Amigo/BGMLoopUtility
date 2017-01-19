#ifndef ACCEPTDROPLABEL_HPP
#define ACCEPTDROPLABEL_HPP

#include <QObject>
#include <QLabel>
#include <QString>
#include <QDragEnterEvent>
#include <QDropEvent>

class AcceptDropLabel : public QLabel
{
    Q_OBJECT

public:
    AcceptDropLabel(QWidget *parent);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    QString getFullPathFromEvent(QDropEvent *event);

signals:
    void fileDropped(QString filename);

};

#endif // ACCEPTDROPLABEL_HPP
