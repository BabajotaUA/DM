#include <QCoreApplication>
#include "download.h"
#include "receiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Download item = Download("http://r8---sn-2gb7ln76.c.youtube.com/videoplayback?key=yt1&id=a75259ca3e098286&fexp=912513%2C913562%2C916807%2C914079%2C924605%2C901208%2C929123%2C929915%2C929906%2C925714%2C929119%2C931202%2C932802%2C928017%2C912515%2C912518%2C911416%2C906906%2C913563%2C904476%2C930807%2C919373%2C906836%2C933701%2C900345%2C912711%2C929606%2C910075&ipbits=8&newshard=yes&ratebypass=yes&sver=3&ms=au&sparams=cp%2Cid%2Cip%2Cipbits%2Citag%2Cratebypass%2Csource%2Cupn%2Cexpire&cp=U0hVTVdNVV9NTkNONV9PR1lJOkpsbHd3VWhUbk1z&upn=7FRLLcjWB8o&ip=194.108.42.139&expire=1368727884&itag=22&mt=1368702380&mv=m&source=youtube&signature=89CDCC3CE23E74DA47138698C173A254D93EEF79.475575945AB3A25BAC65E9175CEE5FF8FEC9A03B&title=Using+the+Quick+Tools+Add-on+in+Blender", "E:/");
    Receiver receiverImplementation = Receiver(&item);
    item.newDownloadFactory(&receiverImplementation);

    QObject::connect(&receiverImplementation, SIGNAL(downloadInfoRecived(QList<QNetworkReply::RawHeaderPair>)),
                     &item, SLOT(setDownloadInfo(QList<QNetworkReply::RawHeaderPair>)));
    QObject::connect(&receiverImplementation, SIGNAL(downloadDataRecived(QByteArray*)),
                     &item, SLOT(saveData(QByteArray*)));

    item.startDownload();

    return a.exec();
}
