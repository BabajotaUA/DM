#include <QCoreApplication>
#include "download.h"
#include "receiver.h"
#include "datasaver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    auto item = Download("http://www.ex.ua/load/55646814", "D:/");   //"http://cs314420.vk.me/v314420355/8b4/6byNiT8qWbw.jpg" "http://www.ex.ua/load/54338428"  "http://www.ex.ua/load/43628663"
    auto receiverImplementation = new Receiver(&item);
    auto dataSaverImplementation = new DataSaver(&item);
    item.newDownloadFactory(receiverImplementation, dataSaverImplementation);

    QObject::connect(receiverImplementation, SIGNAL(downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>)),
                     &item, SLOT(setDownloadInfo(QList<QNetworkReply::RawHeaderPair>)));
    QObject::connect(receiverImplementation, SIGNAL(downloadDataRecived(QByteArray&)),
                     &item, SLOT(saveData(QByteArray&)));
    QObject::connect(receiverImplementation, SIGNAL(downloadBytesDownloaded(qint64)),
                     &item, SLOT(setDownloadProgress(qint64)));

    item.startDownload();

    return a.exec();
}
