#include "datasavermock.h"

DataSaverMock::DataSaverMock(QObject *parent) :
    QObject(parent)
{
}

void DataSaverMock::save(const QByteArray &data, const QList<qint64> &parts)
{
    qDebug() << "(DataSaverMock) Data wil be saved";
}

void DataSaverMock::prepareFiles(const QString &filePath, const QList<qint64> &parts)
{
    qDebug() << "(DataSaverMock) Files will be created at:" << filePath;
}

void DataSaverMock::deleteFiles(bool withDataFile)
{
    if (!withDataFile)
        qDebug() << "(DataSaverMock) Parts file will be deleted";
    else
        qDebug() << "(DataSaverMock) Parts and Data files will be deleted";
}
