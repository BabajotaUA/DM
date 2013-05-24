#include "sender.h"
#include <QDebug>

Sender::Sender(QObject *parent) :
    QObject(parent)
{
}

Sender::~Sender()
{
    qDebug() << "\nSender DELETE!\n";
}

QNetworkReply* Sender::requestDownloadInfo(const QUrl &sourceURL)
{
    request = QNetworkRequest(sourceURL);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    return manager.head(request);
}

QNetworkReply* Sender::requestDownloadData(const QPair<qint64, qint64> &part)
{
    auto rangeHeaderString = "bytes=" + QByteArray::number(part.first) + "-" + QByteArray::number(part.second);
    request.setRawHeader("Range",rangeHeaderString);
    return manager.get(request);
}
