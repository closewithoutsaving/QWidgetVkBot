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
//        qDebug() << answer;

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

        long id;
        if(isConf)
        {
            id = Controller::peer_id_second_thread = 2000000000 + obj5["chat_id"].toInt();
//        qDebug() << id;
        }
        else
        {
            id = Controller::peer_id_second_thread = obj5["user_id"].toDouble();
//        qDebug() << id;
        }

        Parser parser;
        parser.parseMassege(str);

    }
    else {
        answer = "Failure sended\n" + QString(reply->errorString());
//        qDebug() << answer;
    }

    delete reply;

}

void Request::sendMessageWithAttachment(QString attachment, QString message)
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

void Request::adultVideoSearch(QString video)
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
        long musics[count][2];
        QString attachment = "";

        for(int i = 0; i < count; i++)
        {
            QJsonObject obj4 = obj3[i].toObject();

            attachment.append("video");

            musics[i][0] = obj4["owner_id"].toDouble();

            attachment.append(QString::number(musics[i][0]));
            attachment.append("_");

            musics[i][1] = obj4["id"].toDouble();

            attachment.append(QString::number(musics[i][1]));
            attachment.append(",");
        }

        QString message = "По вашему запросу \'" + video + "\' найдено " + QString::number(count) + " видео";
        Request::sendMessageWithAttachment(attachment, message);
    }

    else
    {
        qDebug() << "Fail to send message with video attachment";
    }

}

void Request::videoSearch(QString video)
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
        long musics[count][2];
        QString attachment = "";

        for(int i = 0; i < count; i++)
        {
            QJsonObject obj4 = obj3[i].toObject();

            attachment.append("video");

            musics[i][0] = obj4["owner_id"].toDouble();

            attachment.append(QString::number(musics[i][0]));
            attachment.append("_");

            musics[i][1] = obj4["id"].toDouble();

            attachment.append(QString::number(musics[i][1]));
            attachment.append(",");
        }

        QString message = "По вашему запросу \'" + video + "\' найдено " + QString::number(count) + " видео";
        Request::sendMessageWithAttachment(attachment, message);
    }

    else
    {
        qDebug() << "Fail to send message with video attachment";
    }

}

void Request::docSearch(QString docName)
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
            Request::sendMessage("Документов по запросу " + docName + " не найдено");
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
        Request::sendMessageWithAttachment(attachment, message);
    }

    else
    {
        qDebug() << "Fail to send message with video attachment";
    }
}

void Request::gifSearch(QString gifName)
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
            Request::sendMessage("Гифок по запросу " + gifName + " не найдено");
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

        Request::sendMessageWithAttachment(attachment, message);
    }

    else
        qDebug() << "Fail to send message with video attachment";
}

