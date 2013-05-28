#pragma once
#include <QtCore/QString>
#include <QtCore/QList>

class DataSaverInterface
{
public:
    virtual ~DataSaverInterface() {}
    virtual void prepareFiles(const QString &filePath, const QList<qint64> &parts) = 0;
    virtual void save(const QByteArray &data, const QList<qint64> &parts) = 0;
    virtual void deleteFiles(bool withDataFile = false) = 0;
};
