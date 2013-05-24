#include <QCoreApplication>
#include "download.h"
#include "receiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Download item = Download("http://www.ex.ua/load/49186947", "D:/");
    Receiver receiverImplementation = Receiver(&item);
    item.newDownloadFactory(&receiverImplementation);

    QObject::connect(&receiverImplementation, SIGNAL(downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>)),
                     &item, SLOT(setDownloadInfo(QList<QNetworkReply::RawHeaderPair>)));
    QObject::connect(&receiverImplementation, SIGNAL(downloadDataRecived(QByteArray*)),
                     &item, SLOT(saveData(QByteArray*)));

    item.startDownload();

    return a.exec();
}
