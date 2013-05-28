#include "receivermock.h"
#include <QDebug>

ReceiverMock::ReceiverMock(const QByteArray &data, QObject *parent) :
    QObject(parent)
{
    testData = data;
}

ReceiverMock::~ReceiverMock()
{
    qDebug() << "\nReceiverMock DELETE!\n";
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

QByteArray *ReceiverMock::getDataImmediatly() const
{
    return &testData.left(testData.size()/2);
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
    /*pair.first = "Accept-Ranges";
    pair.second = "bytes";
    testInfoList.append(pair);*/

    return testInfoList;
}
