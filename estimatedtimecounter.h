#pragma once

#include <QObject>

class EstimatedTimeCounter : public QObject
{
    Q_OBJECT
public:
    explicit EstimatedTimeCounter(QObject *parent = nullptr);
    virtual ~EstimatedTimeCounter();
    
};
