#include "downloader.h"

Downloader::Downloader()
{

}

QString Downloader::download(QString url, QString path)
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkRequest req( url );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {

        QFile *file = new QFile(path);

        if(file->open(QFile::WriteOnly))
        {
            file->write(reply->readAll());
            file->close();
        }

        delete file;
        delete reply;

        return "successfuly downloaded";
    }
    else {
        delete reply;

        return "don't downloaded";
    }
}
