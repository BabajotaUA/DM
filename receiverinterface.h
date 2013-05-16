#pragma once
#include <QtNetwork/QNetworkReply>

class ReceiverInterface
{
public:
    virtual ~ReceiverInterface() {}
    virtual void replyReceivingStarted(QNetworkReply*) = 0;
};
