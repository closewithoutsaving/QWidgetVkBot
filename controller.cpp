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
