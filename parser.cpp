#include "parser.h"

Parser::Parser()
{

}

void Parser::parseMassege(QString message)
{
    if(message.contains("!бот, спокойной ноч"))
    {
        message = message.mid(5, message.length() - 1);

        if (message.contains(" "))
            message = message.replace(" ", "+");

        qDebug() << message;

        Request request;
        request.sendMessage("Ночки, сенпай)");

    }

    if(message.contains("!video"))
    {
        message = message.mid(7, message.length() - 1);

        if (message.contains(" "))
            message = message.replace(" ", "+");

        qDebug() << message;

        Video video;
        video.videoSearch(message);
    }

    if(message.contains("!avideo"))
    {
        message = message.mid(8, message.length() - 1);

        if (message.contains(" "))
            message = message.replace(" ", "+");

        qDebug() << message;

        Video video;
        video.adultVideoSearch(message);
    }

    if(message.contains("!doc"))
    {
        message = message.mid(5, message.length() - 1);

        if (message.contains(" "))
            message = message.replace(" ", "+");

        qDebug() << message;

        Doc doc;
        doc.docSearch(message);
    }

    if(message.contains("!gif"))
    {
        message = message.mid(5, message.length() - 1);

        if (message.contains(" "))
            message = message.replace(" ", "+");

        qDebug() << message;

        Gif gif;
        gif.searchGif(message);
    }

}
