#include "gif.h"

Gif::Gif()
{

}

void Gif::searchGif(QString name)
{
    Request request;
    request.gifSearch(name);
}

