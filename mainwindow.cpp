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
        ui->listLog->addItem("bot thread stoped");
    }

}

void MainWindow::on_pushClearLog_clicked()
{
    ui->listLog->clear();
    ui->listLog->addItem("log cleared");
}

void MainWindow::on_pushSetToken_clicked()
{
    Variables::token = ui->lineToken->text();
    ui->listLog->addItem("token has been changed");
}

void MainWindow::on_pushButton_clicked()
{
    Variables::token = "50075c27a07c3007e31c9e0269d5d7ae2875fa7c950b86c34f46409cd487270885dd874ca629136e60521";
}
