#pragma once

#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(const QUrl &sourceURL, QObject *parent = nullptr);
    virtual ~Sender();

    QNetworkReply* requestDownloadInfo();
    QNetworkReply* requestDownloadData(const QPair<qint64, qint64> &part);

private:
    QNetworkRequest request;
    QNetworkAccessManager manager;
};
