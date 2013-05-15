#pragma once

#include <QObject>

class TestDownload : public QObject
{
    Q_OBJECT
public:
    explicit TestDownload(QObject *parent = nullptr);

private slots:
    void testStartDownload();
};
