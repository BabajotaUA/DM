#pragma once

#include <QtCore/QObject>

class PartsController : public QObject
{
    Q_OBJECT
public:
    explicit PartsController(qint64 fileSize, QObject *parent = nullptr);
    virtual ~PartsController();

    void calculation(qint64 partSize, qint64 startByte = 0);
    bool nextPart();
    QPair<qint64, qint64> actual() const;
    QList<qint64> getParts() const;

private:
    QList<qint64> partList;
    qint64 absoluteSize;
};
