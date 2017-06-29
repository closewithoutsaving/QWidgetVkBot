#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QThreadPool>
#include <QListWidget>
#include <QLineEdit>
#include <QFileDialog>
#include <QTimer>
#include <QClipboard>

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

    void on_pushDownload_clicked();

    void on_pushSelectPath_clicked();

    void on_pushClearWindow_clicked();

    void showTime();

    void on_pushCopyRequest_clicked();

    void on_pushClipboardLogClear_clicked();

    void clipboard_changed();

    void on_pushClipboardRemoveLast_clicked();

private:
    VkBotThread* botThread;
    Downloader* down;
    Ui::MainWindow *ui;
    QTimer *timer;
    QClipboard *clipboard;

    QString url;
    QString path;
    QString name;
    QString type;
};

#endif // MAINWINDOW_H
