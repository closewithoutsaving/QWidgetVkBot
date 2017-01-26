#ifndef VKBOTTHREAD_H
#define VKBOTTHREAD_H

#include <QRunnable>
#include <QDebug>
#include <QThread>

#include "request.h"

class VkBotThread : public QRunnable
{
public:
    VkBotThread();

    void run();
};

#endif // VKBOTTHREAD_H
