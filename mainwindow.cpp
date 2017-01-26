#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    botThread = new VkBotThread();
    QThreadPool::globalInstance()->start(botThread);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushStartBot_clicked()
{
    if (!VkBotThread::isSuspended)
    {
        return;
    }

    if(VkBotThread::isSuspended)
    {
        VkBotThread::isSuspended = false;
        ui->listLog->addItem("bot thread srarted");
    }
}

void MainWindow::on_pushStopBot_clicked()
{

    if(VkBotThread::isSuspended)
    {
        ui->listLog->addItem("already suspended");
    }

    if (!VkBotThread::isSuspended)
    {
        VkBotThread::isSuspended = true;
    }

}
