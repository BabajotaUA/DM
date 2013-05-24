#pragma once
#include <QtNetwork/QNetworkReply>
#include <QDebug>

class ReceiverInterface
{
public:
    virtual ~ReceiverInterface() { qDebug() << "\nReceiverInterface DELETE!\n"; }
    virtual void replyReceivingStarted(QNetworkReply*) = 0;
};
