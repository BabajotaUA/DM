#include "sender.h"

Sender::Sender(const QUrl &sourceURL, QObject *parent) :
    QObject(parent)
{
    request = QNetworkRequest(sourceURL);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
}

Sender::~Sender()
{
}


QNetworkReply* Sender::requestDownloadInfo()
{
    return manager.head(request);
}

QNetworkReply* Sender::requestDownloadData(const QPair<qint64, qint64> &part)
{
    auto rangeHeaderString = "bytes=" + QByteArray::number(part.first) + "-" + QByteArray::number(part.second);
    request.setRawHeader("Range",rangeHeaderString);
    return manager.get(request);
}
