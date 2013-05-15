#include "datasaver.h"

DataSaver::DataSaver(const QString &filePath, QObject *parent) :
    QObject(parent)
{
    file.setFileName(filePath);
    partsFile.setFileName(filePath + ".inf");
}

DataSaver::~DataSaver()
{
}

void DataSaver::prepareFiles(const QList<qint64> &parts)
{
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
