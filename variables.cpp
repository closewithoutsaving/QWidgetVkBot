#include "variables.h"

Variables::Variables()
{

}

int Variables::getRandom()
{
    // random number between low and high
    return qrand() % ((20000 + 2) - 2) + 2;
}

//get access token
//https://oauth.vk.com/authorize?client_id=5512525&display=page&redirect_uri=https://oauth.vk.com/authorize&scope=
//messages,video,docs,offline&response_type=token&v=5.57

QString Variables::token = "50075c27a07c3007e31c9e0269d5d7ae2875fa7c950b86c34f46409cd487270885dd874ca629136e60521";
