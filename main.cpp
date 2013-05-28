#include <QCoreApplication>
#include "download.h"
#include "receiver.h"
#include "datasaver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto item = Download("http://www.ex.ua/load/25584124", "D:/");
    auto receiverImplementation = new Receiver(&item);
    auto dataSaverImplementation = new DataSaver(&item);
    item.newDownloadFactory(receiverImplementation, dataSaverImplementation);

    QObject::connect(receiverImplementation, SIGNAL(downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>)),
                     &item, SLOT(setDownloadInfo(QList<QNetworkReply::RawHeaderPair>)));
    QObject::connect(receiverImplementation, SIGNAL(downloadDataRecived(QByteArray*)),
                     &item, SLOT(saveData(QByteArray*)));

    item.startDownload();

    return a.exec();
}
