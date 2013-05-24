#pragma once

#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);
    virtual ~Sender();

    QNetworkReply* requestDownloadInfo(const QUrl &sourceURL);
    QNetworkReply* requestDownloadData(const QPair<qint64, qint64> &part);

private:
    QNetworkRequest request;
    QNetworkAccessManager manager;
};
