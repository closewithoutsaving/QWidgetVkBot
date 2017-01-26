#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QThreadPool>
#include <QListWidget>
#include <QLineEdit>

#include <vkbotthread.h>

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

private:
    VkBotThread* botThread;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
