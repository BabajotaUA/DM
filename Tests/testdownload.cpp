#include <QtTest/QtTest>
#include "QDir"

#include "testdownload.h"
#include "../download.h"

TestDownload::TestDownload(QObject *parent)
{
}

void TestDownload::testStartDownload()
{
    Download item = Download("", QDir::currentPath());
    QVERIFY(item.getState() == Download::NotReady);

    item.startDownload();

}
