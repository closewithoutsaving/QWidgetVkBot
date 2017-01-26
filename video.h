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
};

#endif // VIDEO_H
