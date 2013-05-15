#pragma once

#include "partscontroller.h"
#include "datasaver.h"
#include "receiver.h"
#include "sender.h"
#include "speedcounter.h"
#include "estimatedtimecounter.h"
#include "downloadinterface.h"

class Download : public QObject, public DownloadInterface
{
    Q_OBJECT
public:
    explicit Download(const QString &source, const QString &destination, QObject *parent = nullptr);
    virtual ~Download();

    enum State {NotReady, Downloading, Paused, Finished, Fail};
    
signals:
    void downloadDataChanged();

public:
    void startDownload();
    void pauseDownload();
    void deleteDownload();

    int getState() const;

private slots:
    void setDownloadInfo(const QList<QNetworkReply::RawHeaderPair> &rawHeaders);
    void saveData(QByteArray *data);

private:
    State currentState;
    QUrl sourceURL;
    QString fileName;
    QString fileDestination;
    qint64 fileSize, partSize;

    void newDownloadFactory();
    void prepareDownload();
    void continueDownload();
    bool downloadInfoVerification();

    QSharedPointer<Sender> sender;
    QSharedPointer<Receiver> receiver;
    QSharedPointer<DataSaver> saver;
    QSharedPointer<PartsController> parts;
    QSharedPointer<SpeedCounter> speedCounter;
    QSharedPointer<EstimatedTimeCounter> timeCounter;
};
