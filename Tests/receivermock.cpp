#include "receivermock.h"
#include <QDebug>

ReceiverMock::ReceiverMock(QObject *parent) :
    QObject(parent)
{
    testData = QByteArray("test_value 123");
}

void ReceiverMock::replyReceivingStarted(QNetworkReply *reply)
{
    switch (reply->operation())
    {
    case QNetworkAccessManager::HeadOperation:
        emit downloadInfoRecived(prepareDownloadInfo());
        break;
    case QNetworkAccessManager::GetOperation:
        emit downloadDataRecived(&testData);
        break;
    default:
        break;
    }
}


QList<QNetworkReply::RawHeaderPair> ReceiverMock::prepareDownloadInfo()
{
    auto testDataSize = QString::number(testData.size());
    auto testFileName = "Test File.txt";

    QList<QNetworkReply::RawHeaderPair> testInfoList;

    QNetworkReply::RawHeaderPair pair;
    pair.first = "Content-Length";
    pair.second = testDataSize.toUtf8();
    testInfoList.append(pair);
    pair.first = "Content-Disposition";
    pair.second = QByteArray("attachment; filename=") + '"' + testFileName + '"';
    testInfoList.append(pair);
    pair.first = "Accept-Ranges";
    pair.second = "";
    testInfoList.append(pair);

    qDebug() << "(MOCK) " << testInfoList;

    return testInfoList;
}
