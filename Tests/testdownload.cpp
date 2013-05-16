#include <QtTest>
#include <QDir>
#include <QDebug>

#include "testdownload.h"
#include "../download.h"
#include "receivermock.h"

void TestDownload::testStartDownload()
{
    Download item = Download("http://test_file.txt", QDir::currentPath()+"/");
    ReceiverMock receiver = ReceiverMock(&item);
    item.newDownloadFactory(&receiver);

    QObject::connect(&receiver, SIGNAL(downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>)),
                     &item, SLOT(setDownloadInfo(QList<QNetworkReply::RawHeaderPair>)));
    QObject::connect(&receiver, SIGNAL(downloadDataRecived(QByteArray*)),
                     &item, SLOT(saveData(QByteArray*)));

    QCOMPARE(item.getState(), Download::NotReady);

    item.startDownload();

    QCOMPARE(item.getState(), Download::Downloading);

}
