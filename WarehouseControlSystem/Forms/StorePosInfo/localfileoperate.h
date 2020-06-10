#ifndef LOCALFILEOPERATE_H
#define LOCALFILEOPERATE_H

#include <QObject>
#include <QStringList>
#include <QList>

class LocalFileOperate :public QObject
{
    Q_OBJECT
public:
     LocalFileOperate();
    QList<QStringList> ReadFileData(QString filename);
    bool WriteFileData(QList<QStringList>  Data,QString filename);
};

#endif // LOCALFILEOPERATE_H
