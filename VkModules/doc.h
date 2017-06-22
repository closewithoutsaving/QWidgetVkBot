#ifndef DOC_H
#define DOC_H

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

class Doc
{
public:
    Doc();
    void docSearch(QString docName);
    void sendMessage(QString message);
    void sendMessageWithAttachment(QString attachment, QString message);
};

#endif // DOC_H
