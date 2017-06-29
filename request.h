#ifndef REQUEST_H
#define REQUEST_H

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

#include "variables.h"
#include "controller.h"
#include "parser.h"

class Request
{
public:
    Request();
    void sendRequest();
    void sendMessage(QString message);
    void messagesGetDialogs();
};

#endif // REQUEST_H
