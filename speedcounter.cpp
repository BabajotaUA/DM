#include "speedcounter.h"
#include <QDebug>

SpeedCounter::SpeedCounter(QObject *parent) :
    QObject(parent)
{
}

SpeedCounter::~SpeedCounter()
{
    qDebug() << "\nSpeedCounter DELETE!\n";
}
