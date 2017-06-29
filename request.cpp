#include "request.h"

Request::Request()
{

}

//users.get
void Request::sendRequest()
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl u = QUrl("https://api.vk.com/method/users.get?user_ids=kissloryshy&access_token="
                  + Variables::token);

    QNetworkRequest req( u );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Success" <<reply->readAll();
        delete reply;
    }
    else {
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
}

void Request::sendMessage(QString message)
{
    if(message.contains(" "))
        message = message.replace(" ", "+");

    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl u = QUrl("https://api.vk.com/method/messages.send?&random_id=" + QString::number(Variables::getRandom())
                  + "&peer_id=" + QString::number(Controller::peer_id_second_thread)
                  + "&message=" + message
                  + "&access_token=" + Variables::token
                  + "&v=5.57");

    QNetworkRequest req( u );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    QString answer;
    if (reply->error() == QNetworkReply::NoError) {
        answer = "Success sended\n" + QString(reply->readAll());
        qDebug() << answer;
    }
    else {
        answer = "Failure sended\n" + QString(reply->errorString());
        qDebug() << answer;
    }

    delete reply;
}

void Request::messagesGetDialogs()
{
    QEventLoop eventLoop;

    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl u = QUrl("https://api.vk.com/method/messages.getDialogs?count=10&unread=1&access_token="
                  + Variables::token
                  + "&v=5.57");

    QNetworkRequest req( u );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    QString answer = "";
    if (reply->error() == QNetworkReply::NoError) {

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj1 = doc.object();
        QJsonObject obj2 = obj1["response"].toObject();

        if(obj2["count"].toInt() == 0)
        {
            return;
        }

        QJsonArray obj3 = obj2["items"].toArray();
        QJsonObject obj4 = obj3[0].toObject();
        QJsonObject obj5 = obj4["message"].toObject();

        //Is it conf?
        bool isConf = obj5.contains("admin_id");

        QString str = obj5["body"].toString();

        if(isConf)
        {
            Controller::peer_id_second_thread = 2000000000 + obj5["chat_id"].toInt();
        }
        else
        {
            Controller::peer_id_second_thread = obj5["user_id"].toDouble();
        }

        Parser parser;
        parser.parseMassege(str);

    }
    else
    {
        answer = "Failure sended\n" + QString(reply->errorString());
    }

    delete reply;
}
