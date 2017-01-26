#include "vkbotthread.h"

VkBotThread::VkBotThread()
{

}

void VkBotThread::run()
{
    Request request;

    while (true)
    {
        request.messagesGetDialogs();

        QThread::sleep(3);
    }
}
