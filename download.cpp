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
}

Download::~Download()
{
}

void Download::startDownload()
{
    switch (currentState)
    {
    case NotReady:
        receiver->replyReceivingStarted(sender->requestDownloadInfo(sourceURL));
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
    currentState = Paused;
}

void Download::deleteDownload()
{

}

void Download::changeDownloadURL(const QString &source)
{
    currentState = NotReady;
    sourceURL = QUrl(source);
    receiver->replyReceivingStarted(sender->requestDownloadInfo(sourceURL));
}

Download::State Download::getState() const
{
    return currentState;
}

void Download::setDownloadInfo(const QList<QNetworkReply::RawHeaderPair> &rawHeaders)
{
    qDebug() << rawHeaders;
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
                qDebug() << "DEBUG" << substringBegin;
                fileName = headValue.mid(substringBegin + 10).split('"')[0];
            }
        }

        if (headPair.first == "Accept-Ranges") {
            partSize = 4000000;
        }
    }
    prepareDownload();
}

void Download::saveData(QByteArray *data)
{
    if (parts->nextPart())
    {
        continueDownload();
    }
    else
    {
        currentState = Finished;
        emit downloadDataChanged();
    }
    saver->save(*data, parts->getParts());
}

void Download::newDownloadFactory(ReceiverInterface *receiverImplementation)
{
    sender = QSharedPointer<Sender>(new Sender(this));
    receiver = QSharedPointer<ReceiverInterface>(receiverImplementation);
    speedCounter = QSharedPointer<SpeedCounter>(new SpeedCounter(this));
    timeCounter = QSharedPointer<EstimatedTimeCounter>(new EstimatedTimeCounter(this));
}

void Download::prepareDownload()
{
    if (!downloadInfoVerification())
    {
        currentState = Fail;
        emit downloadDataChanged();
        return;
    }

    parts = QSharedPointer<PartsController>(new PartsController(fileSize, this));
    parts->calculation(partSize);

    saver = QSharedPointer<DataSaver>(new DataSaver(fileDestination + fileName, this));
    saver->prepareFiles(parts->getParts());

    continueDownload();
}

void Download::continueDownload()
{
    receiver->replyReceivingStarted(sender->requestDownloadData(parts->actual()));
    currentState = Downloading;
    emit downloadDataChanged();
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

    qDebug() << "(Download) " << fileName << "size = " << fileSize;

    return true;
}
