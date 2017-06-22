#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDateTime"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    getTokenRequest = "https://oauth.vk.com/authorize?client_id=5938020&display=page&redirect_uri=https://oauth.vk.com/authorize&scope=messages,video,docs,offline&response_type=token&v=5.57";

    botThread = new VkBotThread();
    down = new Downloader();
    QThreadPool::globalInstance()->start(botThread);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    clipboard = QApplication::clipboard();
    connect(clipboard, SIGNAL(dataChanged()), SLOT(clipboard_changed()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete botThread;
    delete down;
    delete timer;
}

void MainWindow::on_pushStartBot_clicked()
{
    if (!VkBotThread::isSuspended)
    {
        ui->listLog->addItem("bot thread already srarted");
        return;
    }

    VkBotThread::isSuspended = false;
    ui->listLog->addItem("bot thread srarted");
}

void MainWindow::on_pushStopBot_clicked()
{

    if(VkBotThread::isSuspended)
    {
        ui->listLog->addItem("already suspended");
        return;
    }

    VkBotThread::isSuspended = true;
    ui->listLog->addItem("bot thread stoped");
}

void MainWindow::on_pushClearLog_clicked()
{
    ui->listLog->clear();
    ui->listLog->addItem("log cleared");
}

void MainWindow::on_pushSetToken_clicked()
{
    Variables::token = this->clipboard->text();
    qDebug() << Variables::token;
    ui->listLog->addItem("token has been pasted");
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
        ui->labelProgress->setText("error in paths");
        return;
    }
    else
    {
        url = ui->lineUrl->text();
        ui->labelProgress->setText("downloading");
        ui->labelProgress->setText(down->download(url, path));
    }
}

void MainWindow::on_pushSelectPath_clicked()
{

/*
    tr - name of window
    3 param - which folder will be open in window
    4 param - filter
*/

//    path = QFileDialog::getOpenFileName(this, tr("Save as"), "/home/", "All files(*.*)");

    path = QFileDialog::getSaveFileName(this, tr("Save as"), "/home/", tr("All files(*.*)"));

    qDebug() << path;

    ui->linePath->setText(path);

}

void MainWindow::on_pushClearWindow_clicked()
{
    ui->lineUrl->setText("");
    ui->linePath->setText("");
    ui->labelProgress->setText("");
}

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString timeText = time.toString("hh : mm : ss");
    ui->labelMoscowTime->setText(timeText);
}

void MainWindow::on_pushCopyRequest_clicked()
{
    clipboard->setText(getTokenRequest);
    ui->listLog->addItem("token request has been copied");
}

void MainWindow::clipboard_changed()
{
    ui->listClipboardLog->addItem(clipboard->text());
}

void MainWindow::on_pushClipboardLogClear_clicked()
{
    ui->listClipboardLog->clear();
}

void MainWindow::on_pushClipboardRemoveLast_clicked()
{
    int count = ui->listClipboardLog->count();
    ui->listClipboardLog->removeItemWidget(ui->listClipboardLog->currentItem());
}
