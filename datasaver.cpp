#include "datasaver.h"
#include <QDebug>

DataSaver::DataSaver(QObject *parent) :
    QObject(parent)
{
}

DataSaver::~DataSaver()
{
    qDebug() << "\nDataSaver DELETE!\n";
}

void DataSaver::prepareFiles(const QString &filePath, const QList<qint64> &parts)
{
    file.setFileName(filePath);
    partsFile.setFileName(filePath + ".inf");
    prepareDestinationFile();
    preparePartsFile(parts);
}

void DataSaver::save(const QByteArray &data, const QList<qint64> &parts)
{
    preparePartsFile(parts);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
        return;

    file.write(data);

    file.flush();
    file.close();
}

void DataSaver::deleteFiles(bool withDataFile)
{
    partsFile.remove();
    if (withDataFile)
        file.remove();
}

void DataSaver::prepareDestinationFile()
{
    if (!file.open(QIODevice::WriteOnly))
        return;

    file.flush();
    file.close();
}

void DataSaver::preparePartsFile(const QList<qint64> &parts)
{
    if (parts.isEmpty())
        return;

    if (!partsFile.open(QIODevice::WriteOnly))
        return;

    foreach (qint64 part, parts)
        partsFile.write(QByteArray::number(part) + ",");

    partsFile.flush();
    partsFile.close();
}
