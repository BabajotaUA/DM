#pragma once

#include <QObject>

class SpeedCounter : public QObject
{
    Q_OBJECT
public:
    explicit SpeedCounter(QObject *parent = nullptr);
    virtual ~SpeedCounter();
};
