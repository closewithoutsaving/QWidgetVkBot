#include "video.h"

Video::Video()
{

}

void Video::videoSearch(QString name)
{
    Request request;
    request.videoSearch(name);
}

void Video::adultVideoSearch(QString name)
{
    Request request;
    request.adultVideoSearch(name);
}
