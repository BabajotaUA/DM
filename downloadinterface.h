#pragma once

class DownloadInterface
{
public:
    virtual ~DownloadInterface() {}
    virtual void startDownload() = 0;
    virtual void pauseDownload() = 0;
    virtual void deleteDownload() = 0;
};
