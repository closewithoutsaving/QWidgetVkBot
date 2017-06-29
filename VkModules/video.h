#ifndef VIDEO_H
#define VIDEO_H

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

class Video
{
public:
    Video();
    void videoSearch(QString name);
    void adultVideoSearch(QString name);
    void sendMessageWithAttachment(QString attachment, QString message);
};

#endif // VIDEO_H
