#include "vkbotthread.h"

VkBotThread::VkBotThread()
{

}

bool VkBotThread::isSuspended = true;

void VkBotThread::run()
{
    Request request;

    while (true)
    {
        if(!isSuspended)
        {
            request.messagesGetDialogs();
        }

        QThread::sleep(3);
    }
}
