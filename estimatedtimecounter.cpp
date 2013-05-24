#include "estimatedtimecounter.h"
#include <QDebug>

EstimatedTimeCounter::EstimatedTimeCounter(QObject *parent) :
    QObject(parent)
{
}

EstimatedTimeCounter::~EstimatedTimeCounter()
{
    qDebug() << "\nEstimatedTimeCounter DELETE!\n";
}
