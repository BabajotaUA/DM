#include "download.h"
#include <QtCore/QStringList>
#include <QDebug>

Download::Download(const QString &source, const QString &destination, QObject *parent) :
    QObject(parent)
{
    currentState = NotReady;
    sourceURL = QUrl(source);
    fileDestination = destination;
    fileName = "";
    fileSize = 0;
    partSize = 0;
    downloadProgress = 0;
    acceptRanges = false;
}

Download::~Download()
{
}

void Download::startDownload()
{
    switch (currentState)
    {
    case NotReady:
        receiver->replyReceivingStarted(sender.requestDownloadInfo(sourceURL));
        return;
    case Paused:
        continueDownload();
        return;
    default:
        return;
    }
}

void Download::pauseDownload()
{
    if (currentState == Downloading)
    {
        auto data = receiver->getDataImmediatly();
        currentState = Paused;
        emit downloadDataChanged();
    }
}

void Download::deleteDownload()
{
}

void Download::changeDownloadURL(const QString &source)
{
    currentState = NotReady;
    sourceURL = QUrl(source);
    receiver->replyReceivingStarted(sender.requestDownloadInfo(sourceURL));
}

Download::State Download::getState() const
{
    return currentState;
}

qreal Download::getProgress() const
{
    return downloadProgress;
}

void Download::setDownloadInfo(const QList<QNetworkReply::RawHeaderPair> &rawHeaders)
{
    foreach (QNetworkReply::RawHeaderPair headPair, rawHeaders) {
        if (headPair.first == "Content-Length")
            fileSize = headPair.second.toLongLong();

        if (headPair.first == "Location")
        {
            changeDownloadURL(headPair.second);
            return;
        }

        if (headPair.first == "Content-Disposition") {
            auto headValue = QString(headPair.second);
            auto substringBegin = headValue.indexOf("filename=");
            if (substringBegin > 0)
            {
                fileName = headValue.mid(substringBegin + 10).split('"')[0];
            }
        }

        if (headPair.first == "Accept-Ranges") {
            partSize = 4000000;
            acceptRanges = true;
        }
    }
    prepareDownload();
}

void Download::setDownloadProgress(qint64 bytesDownloaded)
{
    downloadProgress = 100.0 * bytesDownloaded / fileSize;
    emit downloadDataChanged();
}

void Download::saveData(QByteArray &data)
{
    if (parts.nextPart())
    {
        saver->save(data, parts.getParts());
        continueDownload();
    }
    else
    {
        currentState = Finished;
        saver->save(data, parts.getParts());
        emit downloadDataChanged();
        qDebug() << "\n(Download) FINISHED!\n";
    }
}

void Download::newDownloadFactory(ReceiverInterface *receiverImplementation, DataSaverInterface *dataSaverImplementation)
{
    receiver = QSharedPointer<ReceiverInterface>(receiverImplementation);
    saver = QSharedPointer<DataSaverInterface>(dataSaverImplementation);
}

QString Download::getFileName() const
{
    return fileName;
}

void Download::prepareDownload()
{
    if (!downloadInfoVerification())
    {
        currentState = Fail;
        emit downloadDataChanged();
        return;
    }
    parts.calculation(fileSize, partSize);
    saver->prepareFiles(fileDestination + fileName, parts.getParts());
    emit downloadDataChanged();
    continueDownload();
}

void Download::continueDownload()
{
    currentState = Downloading;
    receiver->replyReceivingStarted(sender.requestDownloadData(parts.actual()));
}

bool Download::downloadInfoVerification()
{
    if (fileSize == 0)
    {
        qDebug() << "\n(Download) ERROR: Data size - invalid\n";
        currentState = Fail;
        return false;
    }

    if (fileName.isEmpty())
        fileName = sourceURL.path().split('/').last();

    if (partSize == 0)
        partSize = fileSize;

    qDebug() << fileName << fileSize << acceptRanges;

    return true;
}
