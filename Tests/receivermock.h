#pragma once

#include <QObject>
#include "../receiverinterface.h"

class ReceiverMock : public QObject, public ReceiverInterface
{
    Q_OBJECT
public:
    explicit ReceiverMock(QObject *parent = nullptr);

    virtual void replyReceivingStarted(QNetworkReply *reply);

signals:
    void downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>);
    void downloadDataRecived(QByteArray *data);

private:
    QList<QNetworkReply::RawHeaderPair> prepareDownloadInfo();
    QByteArray testData;
};
