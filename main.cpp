#include "mainwindow.h"
#include <QApplication>

#include <QThreadPool>

#include <vkbotthread.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //second parallel thread for vkbot (messages.getId)
    VkBotThread* botThread = new VkBotThread();
    QThreadPool::globalInstance()->start(botThread);

    return a.exec();
}
