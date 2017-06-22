#include "gif.h"

Gif::Gif()
{

}

void Gif::searchGif(QString gifName)
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl u = QUrl("https://api.vk.com/method/docs.search?q=" + gifName
                  + "&count=100"
                  + "&access_token=" + Variables::token
                  + "&v=5.57");

    QNetworkRequest req( u );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {

//        qDebug() << "Success sended request gifSearch";

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj1 = doc.object();
        QJsonObject obj2 = obj1["response"].toObject();
        QJsonArray obj3 = obj2["items"].toArray();

        int count = obj3.size();

        if(count == 0)
        {
            Gif::sendMessage("Гифок по запросу " + gifName + " не найдено");
            return;
        }


        int size = 0;
        for(int i = 0; i < count; i++)
        {
            QJsonObject obj4 = obj3[i].toObject();

            if (obj4["ext"] == "gif")
                size++;
        }

        qDebug() << size;

        int countOfGif = 0;

        QString attachment = "";
        long gifs[size][2];

        for(int i = 0; i < size; i++)
        {
            QJsonObject obj4 = obj3[i].toObject();

            if (obj4["ext"] == "gif")
            {
                attachment.append("doc");

                gifs[i][0] = obj4["owner_id"].toDouble();

                attachment.append(QString::number(gifs[i][0]));
                attachment.append("_");

                gifs[i][1] = obj4["id"].toDouble();

                attachment.append(QString::number(gifs[i][1]));
                attachment.append(",");

                countOfGif++;
            }

            else
                continue;
        }

        qDebug() << "attachment = " << attachment;

        QString message = "По вашему запросу \'" + gifName + "\' найдено "
                + QString::number(size) + " документов, из них " + QString::number(countOfGif) + " гифок";

        Gif::sendMessageWithAttachment(attachment, message);
    }

    else
        qDebug() << "Fail to send message with video attachment";
}

void Gif::sendMessage(QString message)
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

void Gif::sendMessageWithAttachment(QString attachment, QString message)
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
