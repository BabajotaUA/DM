#include <QtTest>
#include <QDir>
#include <QDebug>

#include "testdownload.h"
#include "../download.h"
#include "receivermock.h"
#include "datasavermock.h"

void TestDownload::testStartDownload()
{
    auto data = QByteArray("test_value fgdfhdfjhdfgjfgj3");
    auto item = Download("http://test_file.txt", QDir::currentPath()+"/");
    auto receiver = new ReceiverMock(data, &item);
    auto saver = new DataSaverMock(&item);
    item.newDownloadFactory(receiver, saver);
    QSignalSpy spy(&item, SIGNAL(downloadDataChanged()));

    QObject::connect(receiver, SIGNAL(downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>)),
                     &item, SLOT(setDownloadInfo(QList<QNetworkReply::RawHeaderPair>)));
    QObject::connect(receiver, SIGNAL(downloadDataRecived(QByteArray*)),
                     &item, SLOT(saveData(QByteArray*)));

    QCOMPARE(item.getState(), Download::NotReady);

    item.startDownload();

    QCOMPARE(item.getState(), Download::Downloading);

}

void TestDownload::testPauseDownload()
{
    auto data = QByteArray("test_value fgdfhdfjhdfgjfgj3");
    auto item = Download("http://test_file.txt", QDir::currentPath()+"/");
    auto receiver = new ReceiverMock(data, &item);
    auto saver = new DataSaverMock(&item);
    item.newDownloadFactory(receiver, saver);

    QObject::connect(receiver, SIGNAL(downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>)),
                     &item, SLOT(setDownloadInfo(QList<QNetworkReply::RawHeaderPair>)));
    QObject::connect(receiver, SIGNAL(downloadDataRecived(QByteArray*)),
                     &item, SLOT(saveData(QByteArray*)));

    QCOMPARE(item.getState(), Download::NotReady);
    item.pauseDownload();
    QCOMPARE(item.getState(), Download::NotReady);

    item.startDownload();
    item.pauseDownload();
    QCOMPARE(item.getState(), Download::Paused);
}

void TestDownload::testDeleteDownload()
{
    auto data = QByteArray("test_value fgdfhdfjhdfgjfgj3");
    auto item = Download("http://test_file.txt", QDir::currentPath()+"/");
    auto receiver = new ReceiverMock(data, &item);
    auto saver = new DataSaverMock(&item);
    item.newDownloadFactory(receiver, saver);

    QObject::connect(receiver, SIGNAL(downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>)),
                     &item, SLOT(setDownloadInfo(QList<QNetworkReply::RawHeaderPair>)));
    QObject::connect(receiver, SIGNAL(downloadDataRecived(QByteArray*)),
                     &item, SLOT(saveData(QByteArray*)));

    item.deleteDownload();
}


