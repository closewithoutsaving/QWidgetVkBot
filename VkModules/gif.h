#ifndef GIF_H
#define GIF_H

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "request.h"

class Gif
{
public:
    Gif();
    void searchGif(QString gifName);
    void sendMessage(QString message);
    void sendMessageWithAttachment(QString attachment, QString message);
};

#endif // GIF_H
