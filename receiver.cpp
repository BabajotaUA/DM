#include "receiver.h"
#include <QDebug>

Receiver::Receiver(QObject *parent) :
    QObject(parent)
{
}

Receiver::~Receiver()
{
    qDebug() << "n/Receiver DELETE!n/";
}

void Receiver::replyReceivingStarted(QNetworkReply *newReply)
{
    reply = QSharedPointer<QNetworkReply>(newReply);

    connect(reply.data(), SIGNAL(finished()), SLOT(replyReceivingFinished()));
    connect(reply.data(), SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyReceivingError()));
    if (reply->operation() == QNetworkAccessManager::GetOperation)
        connect(reply.data(), SIGNAL(downloadProgress(qint64,qint64)), SLOT(replyReceivingProgress(qint64,qint64)));
}

void Receiver::replyReceivingProgress(qint64 bytesDownloaded, qint64 bytesTotal)
{
}

void Receiver::replyReceivingFinished()
{
    switch (reply->operation())
    {
    case QNetworkAccessManager::HeadOperation:
        emit downloadInfoRecived(reply->rawHeaderPairs());
        break;
    case QNetworkAccessManager::GetOperation:
        emit downloadDataRecived(&reply->readAll());
        break;
    default:
        break;
    }
}

void Receiver::replyReceivingError()
{
    qDebug() << "\n(Receiver) ERROR:" << reply->errorString() << "\n";
}
