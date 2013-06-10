#include "datasavermock.h"

DataSaverMock::DataSaverMock(QObject *parent) :
    QObject(parent)
{
}

void DataSaverMock::save(const QByteArray &data, const QList<qint64> &parts)
{
    qDebug() << "(DataSaverMock) Data wil be saved\n";
    mockData = data;
    mockParts = parts;
}

void DataSaverMock::prepareFiles(const QString &filePath, const QList<qint64> &parts)
{
    qDebug() << "(DataSaverMock) Files will be created at:" << filePath << parts;
    mockFilePath = filePath;
    mockParts = parts;
}

void DataSaverMock::deleteFiles(bool withDataFile)
{
    if (!withDataFile)
        qDebug() << "(DataSaverMock) Parts file will be deleted";
    else
        qDebug() << "(DataSaverMock) Parts and Data files will be deleted";
}

QByteArray DataSaverMock::getMockData() const
{
    return mockData;
}

qint64 DataSaverMock::getMockParts()
{
    return mockParts.size();
}
