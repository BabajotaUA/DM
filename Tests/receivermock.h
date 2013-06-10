#pragma once

#include <QObject>
#include "../receiverinterface.h"

class ReceiverMock : public QObject, public ReceiverInterface
{
    Q_OBJECT
public:
    explicit ReceiverMock(const QByteArray &data, QObject *parent = nullptr);
    virtual ~ReceiverMock();

    virtual void replyReceivingStarted(QNetworkReply *reply);
    QByteArray* getDataImmediatly() const;

signals:
    void downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>);
    void downloadDataRecived(QByteArray &data);

private:
    QList<QNetworkReply::RawHeaderPair> prepareDownloadInfo();
    QByteArray testData;
};
