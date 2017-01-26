#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

//this id from kissloryshy main page
long Controller::peer_id_second_thread = 279100995;
long Controller::peer_id = 279100995;

void Controller::sendMessageFromTextField(const QString &message)
{
    Request request;

    request.sendMessage(message);
}

void Controller::changeId(int index)
{
    switch (index) {
    case 0:
        Controller::peer_id = 279100995;
        qDebug() << Controller::peer_id;
        break;
    case 1:
        Controller::peer_id = 61227081;
        qDebug() << Controller::peer_id;
        break;
    case 2:
        Controller::peer_id = 2000000002;
        qDebug() << Controller::peer_id;
        break;
    default:
        break;
    }
}
