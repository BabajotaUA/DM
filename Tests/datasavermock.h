#pragma once
#include <QDebug>
#include "../datasaverinterface.h"
#include <QObject>

class DataSaverMock : public QObject, public DataSaverInterface
{
    Q_OBJECT
public:
    explicit DataSaverMock(QObject *parent = 0);
    virtual ~DataSaverMock() { }
    void save(const QByteArray &data, const QList<qint64> &parts);
    void prepareFiles(const QString &filePath, const QList<qint64> &parts);
    void deleteFiles(bool withDataFile);

    QByteArray getMockData() const;
    qint64 getMockParts();

private:
    QByteArray mockData;
    QList<qint64> mockParts;
    QString mockFilePath;
    
};
