#pragma once
#include <QtNetwork/QNetworkReply>

class ReceiverInterface
{
public:
    virtual ~ReceiverInterface() {}
    virtual void replyReceivingStarted(QNetworkReply*) = 0;
    virtual QByteArray* getDataImmediatly() const = 0;
};
