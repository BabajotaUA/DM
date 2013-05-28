#pragma once

#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QSharedPointer>
#include "receiverinterface.h"

class Receiver : public QObject, public ReceiverInterface
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
    virtual ~Receiver();

    void replyReceivingStarted(QNetworkReply *newReply);
    QByteArray* getDataImmediatly() const;

signals:
    void downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>);
    void downloadDataRecived(QByteArray *data);

private slots:
    void replyReceivingProgress(qint64 bytesDownloaded, qint64 bytesTotal);
    void replyReceivingFinished();
    void replyReceivingError();

private:
    QSharedPointer<QNetworkReply> reply;
};
