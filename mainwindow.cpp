#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    botThread = new VkBotThread();
    down = new Downloader();
    QThreadPool::globalInstance()->start(botThread);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete botThread;
    delete down;
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
    Variables::token = "b4ef0c44134fc818ba859b30fd102a82704b6dbe87100427b3febc25f52018e66cf3f9f2c8ba50c1d5e0d";
}

void MainWindow::on_pushDownload_clicked()
{

/*
    examples from docs:
    QString().isNull();               // returns true
    QString().isEmpty();              // returns true

    QString("").isNull();             // returns false
    QString("").isEmpty();            // returns true

    QString("abc").isNull();          // returns false
    QString("abc").isEmpty();         // returns false
*/

    if(QString(path).isEmpty())
    {
        ui->labelProgress->text() = "error in paths";
        return;
    }

    else
    {
        url = ui->lineUrl->text();

        ui->labelProgress->text() = "downloading";
        ui->labelProgress->text() = down->download(url, path);
    }

}

void MainWindow::on_pushSelectPath_clicked()
{

/*
    tr - name of window
    3 param - which folder will be open in window
    4 param - filter
*/

    path = QFileDialog::getOpenFileName(this, tr("Save as"), "/home/", "All files(*.*)");

    qDebug() << path;

    ui->labelPath->text() = path;

}
