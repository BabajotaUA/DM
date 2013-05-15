#pragma once

class ReceiverInterface
{
public:
    virtual ~ReceiverInterface() {}
    virtual void replyReceivingStarted(QNetworkReply*) = 0;
};
