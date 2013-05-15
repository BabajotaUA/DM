#include <QCoreApplication>
#include "download.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Download item = Download("http://r10---sn-n8v7sn7s.c.youtube.com/videoplayback?ipbits=8&itag=22&key=yt1&ip=194.186.246.58&newshard=yes&ratebypass=yes&sver=3&mt=1368524478&fexp=905608%2C924601%2C930802%2C911305%2C916611%2C926904%2C904479%2C901208%2C929123%2C929915%2C929906%2C925714%2C929119%2C931202%2C928017%2C912518%2C911416%2C904476%2C930807%2C919373%2C906836%2C933701%2C900345%2C926403%2C912711%2C929606%2C910075&id=4e6c33215143bc85&cp=U0hVTVVPVF9KUENONV9NSVhHOlNkS1hodUt0b21L&expire=1368546656&sparams=cp%2Cid%2Cip%2Cipbits%2Citag%2Cratebypass%2Csource%2Cupn%2Cexpire&ms=au&source=youtube&upn=FGsQNNySpRs&mv=m&signature=013B2FD1A550AFA057FC6825E11942D97791E78F.01B4844277D4C1185A60E500A2179D703EA27C9D&title=%D0%92%D1%96%D1%80%D1%88+%D0%AF+%D0%BD%D0%B5+%D0%B1%D0%BE%D1%8E%D1%81%D1%8C", "E:/");
    item.startDownload();

    return a.exec();
}
