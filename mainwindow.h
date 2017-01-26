#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QThreadPool>
#include <QListWidget>

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

private:
    Ui::MainWindow *ui;
    VkBotThread* botThread;
};

#endif // MAINWINDOW_H
