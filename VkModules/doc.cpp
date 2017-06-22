#include "doc.h"

Doc::Doc()
{

}

void Doc::docSearch(QString docName)
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl u = QUrl("https://api.vk.com/method/docs.search?q=" + docName
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

        if(count == 0)
        {
            Doc::sendMessage("Документов по запросу " + docName + " не найдено");
            return;
        }


        long musics[count][2];
        QString attachment = "";

        for(int i = 0; i < count; i++)
        {
            QJsonObject obj4 = obj3[i].toObject();

            attachment.append("doc");

            musics[i][0] = obj4["owner_id"].toDouble();

            attachment.append(QString::number(musics[i][0]));
            attachment.append("_");

            musics[i][1] = obj4["id"].toDouble();

            attachment.append(QString::number(musics[i][1]));
            attachment.append(",");
        }

        QString message = "По вашему запросу \'" + docName + "\' найдено " + QString::number(count) + " документов";
        Doc::sendMessageWithAttachment(attachment, message);
    }

    else
    {
        qDebug() << "Fail to send message with video attachment";
    }
}

void Doc::sendMessage(QString message)
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

void Doc::sendMessageWithAttachment(QString attachment, QString message)
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
