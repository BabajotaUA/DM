#include "partscontroller.h"
#include <QDebug>
#include <QtCore/QPair>

PartsController::PartsController(qint64 fileSize, QObject *parent) :
    QObject(parent)
{
    absoluteSize = fileSize;
}

PartsController::~PartsController()
{
}

void PartsController::calculation(qint64 partSize, qint64 startByte)
{
    for (auto endByte = startByte; endByte < absoluteSize; endByte += partSize)
        partList.append(endByte);
    partList.append(absoluteSize);
}

bool PartsController::nextPart()
{
    if (partList.size() <= 2) {
        partList.clear();
        return false;
    }
    else {
        partList.removeFirst();
    }
    return true;
}

QPair<qint64, qint64> PartsController::actual() const
{
    return QPair<qint64, qint64>(partList[0], (partList[1]-1));
}

QList<qint64> PartsController::getParts() const
{
    return partList;
}
