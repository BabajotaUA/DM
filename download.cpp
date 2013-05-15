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

    qDebug() << "Download created";
}

Download::~Download()
{
}

void Download::startDownload()
{
    switch (currentState)
    {
    case NotReady:
        newDownloadFactory();
        receiver->replyReceivingStarted(sender->requestDownloadInfo());
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

int Download::getState() const
{
    return currentState;
}

void Download::setDownloadInfo(const QList<QNetworkReply::RawHeaderPair> &rawHeaders)
{
    foreach (QNetworkReply::RawHeaderPair headPair, rawHeaders) {
        if (headPair.first == "Content-Length")
            fileSize = headPair.second.toLongLong();

        if (headPair.first == "Content-Disposition") {
            auto headValue = QString(headPair.second);
            auto substringBegin = headValue.indexOf("filename=");
            if (substringBegin)
                fileName = headValue.mid(substringBegin + 10).split('"')[0];
        }

        if (headPair.first == "Accept-Ranges") {
            partSize = 4000000;
        }
    }
    prepareDownload();
}

void Download::saveData(QByteArray *data)
{
    qDebug()<< "Data recived";
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

void Download::newDownloadFactory()
{
    sender = QSharedPointer<Sender>(new Sender(sourceURL, this));
    receiver = QSharedPointer<Receiver>(new Receiver(this));
    speedCounter = QSharedPointer<SpeedCounter>(new SpeedCounter(this));
    timeCounter = QSharedPointer<EstimatedTimeCounter>(new EstimatedTimeCounter(this));

    connect(receiver.data(), SIGNAL(downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>)), SLOT(setDownloadInfo(QList<QNetworkReply::RawHeaderPair>)));
    connect(receiver.data(), SIGNAL(downloadDataRecived(QByteArray*)), SLOT(saveData(QByteArray*)));
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
        return false;

    if (fileName.isEmpty())
        fileName = sourceURL.path().split('/').last();

    qDebug() << fileName << "\nsize = " << fileSize;

    return true;
}
