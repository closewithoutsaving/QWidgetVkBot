#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QThreadPool>
#include <QListWidget>
#include <QLineEdit>
#include <QFileDialog>

#include "vkbotthread.h"
#include "downloader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushStartBot_clicked();

    void on_pushStopBot_clicked();

    void on_pushClearLog_clicked();

    void on_pushSetToken_clicked();

    void on_pushButton_clicked();

    void on_pushDownload_clicked();

    void on_pushSelectPath_clicked();

private:
    VkBotThread* botThread;
    Downloader* down;
    Ui::MainWindow *ui;

    QString url;
    QString path;
    QString name;
    QString type;
};

#endif // MAINWINDOW_H
