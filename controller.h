#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "variables.h"
#include "request.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    QString answerJson;
    static long peer_id_second_thread;
    static long peer_id;

signals:

public slots:
    void sendMessageFromTextField(const QString &msg);
    void changeId(int);

};

#endif // CONTROLLER_H
