#pragma once

#include "partscontroller.h"
#include "datasaverinterface.h"
#include "receiverinterface.h"
#include "sender.h"
#include "speedcounter.h"
#include "estimatedtimecounter.h"
#include "downloadinterface.h"
#include <QtCore/QSharedPointer>

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

    void newDownloadFactory(ReceiverInterface *receiverImplementation, DataSaverInterface *dataSaverImplementation);
    QString getFileName() const;
    State getState() const;
    qreal getProgress() const;

public slots:
    void setDownloadInfo(const QList<QNetworkReply::RawHeaderPair> &rawHeaders);
    void setDownloadProgress(qint64 bytesDownloaded);
    void saveData(QByteArray &data);

private:
    State currentState;
    QUrl sourceURL;
    QString fileName;
    QString fileDestination;
    qint64 fileSize, partSize;
    qreal downloadProgress;
    bool acceptRanges;

    void prepareDownload();
    void continueDownload();
    bool downloadInfoVerification();
    void changeDownloadURL(const QString &source);

    Sender sender;
    QSharedPointer<ReceiverInterface> receiver;
    QSharedPointer<DataSaverInterface> saver;
    PartsController parts;
    SpeedCounter speedCounter;
    EstimatedTimeCounter timeCounter;
};
