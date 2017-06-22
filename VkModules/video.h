#ifndef VIDEO_H
#define VIDEO_H

#include <QString>
#include <request.h>

class Video
{
public:
    Video();

    void videoSearch(QString name);
    void adultVideoSearch(QString name);
    void sendMessageWithAttachment(QString attachment, QString message);
};

#endif // VIDEO_H
