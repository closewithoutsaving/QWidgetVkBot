#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QString>
#include <QLineEdit>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
#include <QUrlQuery>
#include <QFile>
#include <QLabel>

class Downloader
{
public:
    Downloader();

    QString download(QString url, QString path);
};

#endif // DOWNLOADER_H
