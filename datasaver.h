#pragma once

#include <QtCore/QObject>
#include <QtCore/QFile>

class DataSaver : public QObject
{
    Q_OBJECT
public:
    explicit DataSaver(QObject *parent = nullptr);
    virtual ~DataSaver();

    void prepareFiles(const QString &filePath, const QList<qint64> &parts);
    void save(const QByteArray &data, const QList<qint64> &parts);

private:
    void prepareDestinationFile();
    void preparePartsFile(const QList<qint64> &parts);

    QFile file, partsFile;
};
