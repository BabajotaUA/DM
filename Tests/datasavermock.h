#pragma once
#include <QDebug>
#include "../datasaverinterface.h"
#include <QObject>

class DataSaverMock : public QObject, public DataSaverInterface
{
    Q_OBJECT
public:
    explicit DataSaverMock(QObject *parent = 0);
    virtual ~DataSaverMock() { qDebug() << "\nDataSaverMock DELETE!\n"; }
    void save(const QByteArray &data, const QList<qint64> &parts);
    void prepareFiles(const QString &filePath, const QList<qint64> &parts);
    void deleteFiles(bool withDataFile);
    
};
