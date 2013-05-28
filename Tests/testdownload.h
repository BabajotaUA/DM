#pragma once

#include <QObject>
#include "../download.h"

class TestDownload : public QObject
{
    Q_OBJECT

private slots:
    void testStartDownload();
    void testPauseDownload();
    void testDeleteDownload();
};
