#pragma once

#include <QObject>

class TestDownload : public QObject
{
    Q_OBJECT

private slots:
    void testStartDownload();
};
