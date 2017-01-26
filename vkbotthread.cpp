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
            qDebug() << "bot thread";
        }

        QThread::sleep(3);
    }
}
