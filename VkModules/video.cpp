#include "video.h"

Video::Video()
{

}

void Video::videoSearch(QString video)
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl u = QUrl("https://api.vk.com/method/video.search?q=" + video
                  + "&auto_complete=1"
                  + "&sort=2"
                  + "&adult=0"
                  + "&count=10"
                  + "&access_token=" + Variables::token
                  + "&v=5.57");

    QNetworkRequest req( u );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj1 = doc.object();
        QJsonObject obj2 = obj1["response"].toObject();
        QJsonArray obj3 = obj2["items"].toArray();

        int count = obj3.size();
        long videos[count][2];
        QString attachment = "";

        for(int i = 0; i < count; i++)
        {
            QJsonObject obj4 = obj3[i].toObject();

            attachment.append("video");

            videos[i][0] = obj4["owner_id"].toDouble();

            attachment.append(QString::number(videos[i][0]));
            attachment.append("_");

            videos[i][1] = obj4["id"].toDouble();

            attachment.append(QString::number(videos[i][1]));
            attachment.append(",");
        }

        QString message = "По вашему запросу \'" + video + "\' найдено " + QString::number(count) + " видео";
        Video::sendMessageWithAttachment(attachment, message);
    }

    else
    {
        qDebug() << "Fail to send message with video attachment";
    }

    delete reply;
}

void Video::adultVideoSearch(QString video)
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl u = QUrl("https://api.vk.com/method/video.search?q=" + video
                  + "&auto_complete=1"
                  + "&sort=2"
                  + "&adult=1"
                  + "&count=10"
                  + "&access_token=" + Variables::token
                  + "&v=5.57");

    QNetworkRequest req( u );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj1 = doc.object();
        QJsonObject obj2 = obj1["response"].toObject();
        QJsonArray obj3 = obj2["items"].toArray();

        int count = obj3.size();
        long videos[count][2];
        QString attachment = "";

        for(int i = 0; i < count; i++)
        {
            QJsonObject obj4 = obj3[i].toObject();

            attachment.append("video");

            videos[i][0] = obj4["owner_id"].toDouble();

            attachment.append(QString::number(videos[i][0]));
            attachment.append("_");

            videos[i][1] = obj4["id"].toDouble();

            attachment.append(QString::number(videos[i][1]));
            attachment.append(",");
        }

        QString message = "По вашему запросу \'" + video + "\' найдено " + QString::number(count) + " видео";
        Video::sendMessageWithAttachment(attachment, message);
    }

    else
    {
        qDebug() << "Fail to send message with video attachment";
    }

    delete reply;
}

void Video::sendMessageWithAttachment(QString attachment, QString message)
{
    if (message.contains(""))
        message = message.replace(" ", "+");

    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl u = QUrl("https://api.vk.com/method/messages.send?&random_id=" + QString::number(Variables::getRandom())
                  + "&peer_id=" + QString::number(Controller::peer_id_second_thread)
                  + "&message=" + message
                  + "&attachment=" + attachment
                  + "&access_token=" + Variables::token
                  + "&v=5.57");

    QNetworkRequest req( u );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << reply->readAll();
    }
    else
    {
        qDebug() << reply->errorString();
    }

    delete reply;
}
